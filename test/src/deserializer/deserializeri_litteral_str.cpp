#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <fstream>
#include <sstream>
#include <iostream>

#include "json.hpp"

Test(deserializer_litteral_str, empty_input)
{
    json::JsonValue j = ""_json;

    cr_assert_eq(j, json::JsonValue::Null());
    cr_assert_eq(j, nullptr);
}

Test(deserializer_litteral_str, null)
{
    json::JsonValue j = "null"_json;

    cr_assert_eq(j, json::JsonValue::Null());
    cr_assert_eq(j, nullptr);
}

Test(deserializer_litteral_str, boolean_true)
{
    json::JsonValue j = "true"_json;

    cr_assert_eq(j, json::JsonValue(true));
    cr_assert_eq(j, true);
}

Test(deserializer_litteral_str, boolean_false)
{
    json::JsonValue j = "false"_json;

    cr_assert_eq(j, json::JsonValue(false));
    cr_assert_eq(j, false);
}

Test(deserilizer_litteral_str, empty_json_string)
{
    json::JsonValue j = "\"\""_json;

    cr_assert_eq(j, json::JsonValue(""));
    cr_assert_eq(j == "", true);
}

Test(deserilizer_litteral_str, json_string)
{
    json::JsonValue j = "\"test\""_json;

    cr_assert_eq(j, json::JsonValue("test"));
    cr_assert_eq(j, "test");
}

Test(deserilizer_litteral_str, json_number_int)
{
    json::JsonValue j = "5"_json;

    cr_assert_eq(j, json::JsonValue(5));
    cr_assert_eq(j, 5);
}

Test(deserilizer_litteral_str, json_number_zero)
{
    json::JsonValue j = "0"_json;

    cr_assert_eq(j, json::JsonValue(0));
    cr_assert_eq(j, 0);
}

Test(deserilizer_litteral_str, json_number_float)
{
    json::JsonValue j = "5.5"_json;

    cr_assert_eq(j, json::JsonValue(5.5));
    cr_assert_eq(j, 5.5);
}

Test(deserilizer_litteral_str, json_empty_array)
{
    json::JsonValue j = "[]"_json;

    cr_assert_eq(j, json::JsonValue::Array());
}

Test(deserilizer_litteral_str, json_array)
{
    json::JsonValue j = "[12, \"test\", true, null, {}, {\"test\": 36}, [], [24]]"_json;

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

Test(deserilizer_litteral_str, json_empty_object)
{
    json::JsonValue j = "{}"_json;

    cr_assert_eq(j, json::JsonValue::Object());
}

Test(deserilizer_litteral_str, json_object)
{
    json::JsonValue j = "{\"testNumber\": 12, \"testString\": \"test\", \"testBool\": true, \"testNull\": null, \"testArray\": [12], \"testObject\": { \"test\": 24}}"_json;

    cr_assert_neq(j, json::JsonValue::Object());
    cr_assert_eq(j["testNumber"], 12);
    cr_assert_eq(j["testString"], "test");
    cr_assert_eq(j["testBool"], true);
    cr_assert_eq(j["testNull"], nullptr);
    cr_assert_eq(j["testArray"][0], 12);
    cr_assert_eq(j["testObject"]["test"], 24);
}