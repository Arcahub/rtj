#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <fstream>
#include <sstream>
#include <iostream>

#include "json.hpp"

Test(deserializer_istream, empty_input)
{
    std::stringstream ss;
    json::JsonValue j;

    ss >> j;
    cr_assert_eq(j, json::JsonValue::Null());
    cr_assert_eq(j, nullptr);
}

Test(deserializer_istream, null)
{
    std::stringstream ss("null");
    json::JsonValue j;

    ss >> j;
    cr_assert_eq(j, json::JsonValue::Null());
    cr_assert_eq(j, nullptr);
}

Test(deserializer_istream, boolean_true)
{
    std::stringstream ss("true");
    json::JsonValue j;

    ss >> j;
    cr_assert_eq(j, json::JsonValue(true));
    cr_assert_eq(j, true);
}

Test(deserializer_istream, boolean_false)
{
    std::stringstream ss("false");
    json::JsonValue j;

    ss >> j;
    cr_assert_eq(j, json::JsonValue(false));
    cr_assert_eq(j, false);
}

Test(deserilizer_istream, empty_json_string)
{
    std::stringstream ss("\"\"");
    json::JsonValue j;

    ss >> j;
    cr_assert_eq(j, json::JsonValue(""));
    cr_assert_eq(j == "", true);
}

Test(deserilizer_istream, json_string)
{
    std::stringstream ss("\"test\"");
    json::JsonValue j;

    ss >> j;
    cr_assert_eq(j, json::JsonValue("test"));
    cr_assert_eq(j, "test");
}

Test(deserilizer_istream, json_number_int)
{
    std::stringstream ss("5");
    json::JsonValue j;

    ss >> j;
    cr_assert_eq(j, json::JsonValue(5));
    cr_assert_eq(j, 5);
}

Test(deserilizer_istream, json_number_zero)
{
    std::stringstream ss("0");
    json::JsonValue j;

    ss >> j;
    cr_assert_eq(j, json::JsonValue(0));
    cr_assert_eq(j, 0);
}

Test(deserilizer_istream, json_number_float)
{
    std::stringstream ss("5.5");
    json::JsonValue j;

    ss >> j;
    cr_assert_eq(j, json::JsonValue(5.5));
    cr_assert_eq(j, 5.5);
}

Test(deserilizer_istream, json_empty_array)
{
    std::stringstream ss("[]");
    json::JsonValue j;

    ss >> j;
    cr_assert_eq(j, json::JsonValue::Array());
}

Test(deserilizer_istream, json_array)
{
    std::stringstream ss("[12, \"test\", true, null, {}, {\"test\": 36}, [], [24]]");
    json::JsonValue j;

    ss >> j;
    cr_assert_neq(j, json::JsonValue::Array());
    cr_assert_eq(j[0], 12);
    cr_assert_eq(j[1], "test");
    cr_assert_eq(j[2], true);
    cr_assert_eq(j[3], nullptr);
    cr_assert_eq(j[4], json::JsonValue::Object());
    cr_assert_eq(j[5]["test"], 36);
    cr_assert_eq(j[6], json::JsonValue::Array());
    cr_assert_eq(j[7][0], 24);
}

Test(deserilizer_istream, json_empty_object)
{
    std::stringstream ss("{}");
    json::JsonValue j;

    ss >> j;
    cr_assert_eq(j, json::JsonValue::Object());
}

Test(deserilizer_istream, json_object)
{
    std::stringstream ss("{\"testNumber\": 12, \"testString\": \"test\", \"testBool\": true, \"testNull\": null, \"testArray\": [12], \"testObject\": { \"test\": 24}}");
    json::JsonValue j;

    ss >> j;
    cr_assert_neq(j, json::JsonValue::Object());
    cr_assert_eq(j["testNumber"], 12);
    cr_assert_eq(j["testString"], "test");
    cr_assert_eq(j["testBool"], true);
    cr_assert_eq(j["testNull"], nullptr);
    cr_assert_eq(j["testArray"][0], 12);
    cr_assert_eq(j["testObject"]["test"], 24);
}