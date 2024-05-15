#include "spk_utils/hash.hpp"

#include <catch2/catch_test_macros.hpp>
#include <string>

using namespace spk::hash;
using std::string;

TEST_CASE ("Hashes a string") {
    string test_str = "A string to be hashed for a test";
    string incorrect_test_str =
        "Another string to be hashed for a test";
    string hash_str;
    REQUIRE_NOTHROW (hash_str = hash (test_str));
    SECTION ("Verifies hash for correct string") {
        REQUIRE (check_hash (test_str, hash_str));
    }
    SECTION ("Rejects hash for incorrect string") {
        REQUIRE_FALSE (check_hash (incorrect_test_str, hash_str));
    }
}
