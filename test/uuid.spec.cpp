#include "spk_utils/uuid.hpp"

#include <catch2/catch_test_macros.hpp>
#include <string>

using namespace spk::uuid;
using std::string;

void test_deep_equality (const UUID& uuid1, const UUID& uuid2) {
    SECTION ("contain equal data") {
        REQUIRE (uuid1.get () == uuid2.get ());
    }
    SECTION ("convert to equal strings") {
        REQUIRE (uuid1.to_string () == uuid2.to_string ());
    }
}
void test_equality (const UUID& uuid1, const UUID& uuid2) {
    SECTION ("are 'equal'") { REQUIRE (uuid1 == uuid2); }
    SECTION ("are not 'not equal'") {
        REQUIRE_FALSE (uuid1 != uuid2);
    }
}
void test_negative_equality (const UUID& uuid1, const UUID& uuid2) {
    SECTION ("are not 'equal'") { REQUIRE_FALSE (uuid1 == uuid2); }
    SECTION ("are 'not equal'") { REQUIRE (uuid1 != uuid2); }
}
void test_lengths (const UUID& uuid) {
    SECTION ("evalutes to boolean true") { REQUIRE (uuid); }
    SECTION ("has length 16") {
        REQUIRE (uuid.get ().size () == 16);
    }
}

TEST_CASE ("Unset UUID") {
    UUID uuid;
    SECTION ("and another unset uuid") {
        test_equality (uuid, UUID ());
    }
    SECTION ("evaluates to boolean false") { REQUIRE_FALSE (uuid); }
    SECTION ("throws if get() is called") {
        REQUIRE_THROWS_AS (uuid.get (), Unset_UUID);
    }
    SECTION ("throws if to_string() is called") {
        REQUIRE_THROWS_AS (uuid.to_string (), Unset_UUID);
    }
}

TEST_CASE ("Random UUID") {
    UUID uuid1 = UUID::create ();
    SECTION ("has string of length 36") {
        REQUIRE (uuid1.to_string ().size () == 36);
    }
    test_lengths (uuid1);
    SECTION ("and one made from same string") {
        UUID uuid2 (uuid1.get ());
        test_equality (uuid1, uuid2);
        test_deep_equality (uuid1, uuid2);
    }
    SECTION ("and one made from same data") {
        UUID uuid2 = UUID::read (uuid1.to_string ());
        test_equality (uuid1, uuid2);
        test_deep_equality (uuid1, uuid2);
    }
    SECTION ("and another random UUID") {
        UUID uuid2 = UUID::create ();
        test_negative_equality (uuid1, uuid2);
        SECTION ("have different data") {
            REQUIRE (uuid1.get () != uuid2.get ());
        }
        SECTION ("convert to different strings") {
            REQUIRE (uuid1.to_string () != uuid2.to_string ());
        }
    }
    SECTION ("and an unset UUID") {
        UUID uuid2;
        test_negative_equality (uuid1, uuid2);
    }
}

TEST_CASE ("Can create UUID from valid string") {
    REQUIRE_NOTHROW (
        UUID::read ("c8581461-e1c7-4bf5-9433-9e2972b9e0ec"));
}
TEST_CASE ("Can't create UUID from invalid string") {
    REQUIRE_THROWS_AS (UUID::read ("not a uuid"), UUID_Error);
    REQUIRE_NOTHROW (
        UUID::read ("c8581461-e1c7-4bf5-9433-9e2972b9e0ec"));
}
