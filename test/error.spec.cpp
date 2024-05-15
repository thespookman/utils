#include "spk_utils/error.hpp"

#include <catch2/catch_test_macros.hpp>
#include <string>

using spk::err::Error;
using std::exception;
using std::string;

string error_message = "A test error message";

SPK_ERR (Test_Error, error_message);

TEST_CASE ("Can catch a simple error as std::exception") {
    string ret = "";
    try {
        throw Test_Error ();
    } catch (exception& e) { ret = e.what (); }
    REQUIRE (ret == error_message);
}

TEST_CASE ("Can catch a simple error as Error") {
    string ret = "";
    try {
        throw Test_Error ();
    } catch (Error& e) { ret = e.what (); }
    REQUIRE (ret == error_message);
}
