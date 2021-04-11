#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <fstream>
#include <iostream>

#include "json.hpp"

Test(deserializer_ifstream, empty_input)
{
    std::ifstream file("./test/source/empty_file.json/");
    json::JsonValue j;

    file >> j;

    cr_assert_eq(j, json::JsonValue::Null());
    cr_assert_eq(j, nullptr);
    file.close();
}

Test(deserializer_ifstream, null)
{
    std::ifstream file("./test/source/direct/null.json");
    json::JsonValue j;

    file >> j;
    cr_assert_eq(j, json::JsonValue::Null());
    cr_assert_eq(j, nullptr);
    file.close();
}

Test(deserializer_ifstream, boolean_true)
{
    std::ifstream file("./test/source/direct/bool_true.json");
    json::JsonValue j;

    file >> j;
    cr_assert_eq(j, json::JsonValue(true));
    cr_assert_eq(j, true);
    file.close();
}

Test(deserializer_ifstream, boolean_false)
{
    std::ifstream file("./test/source/direct/bool_false.json");
    json::JsonValue j;

    file >> j;
    cr_assert_eq(j, json::JsonValue(false));
    cr_assert_eq(j, false);
    file.close();
}

Test(deserilizer_ifstream, empty_json_string)
{
    std::ifstream file("./test/source/direct/empty_string.json");
    json::JsonValue j;

    file >> j;
    cr_assert_eq(j, json::JsonValue(""));
    cr_assert_eq(j == "", true);
    file.close();
}

Test(deserilizer_ifstream, json_string)
{
    std::ifstream file("./test/source/direct/string.json");
    json::JsonValue j;

    file >> j;
    cr_assert_eq(j, json::JsonValue("test"));
    cr_assert_eq(j, "test");
    file.close();
}

Test(deserilizer_ifstream, json_number_int)
{
    std::ifstream file("./test/source/direct/number_int.json");
    json::JsonValue j;

    file >> j;
    cr_assert_eq(j, json::JsonValue(5));
    cr_assert_eq(j, 5);
    file.close();
}

Test(deserilizer_ifstream, json_number_zero)
{
    std::ifstream file("./test/source/direct/number_zero.json");
    json::JsonValue j;

    file >> j;
    cr_assert_eq(j, json::JsonValue(0));
    cr_assert_eq(j, 0);
    file.close();
}

Test(deserilizer_ifstream, json_number_float)
{
    std::ifstream file("./test/source/direct/number_float.json");
    json::JsonValue j;

    file >> j;
    cr_assert_eq(j, json::JsonValue(5.5));
    cr_assert_eq(j, 5.5);
    file.close();
}

Test(deserilizer_ifstream, json_empty_array)
{
    std::ifstream file("./test/source/direct/empty_array.json");
    json::JsonValue j;

    file >> j;
    cr_assert_eq(j, json::JsonValue::Array());
    file.close();
}

Test(deserilizer_ifstream, json_array)
{
    std::ifstream file("./test/source/direct/array.json");
    json::JsonValue j;

    file >> j;
    cr_assert_neq(j, json::JsonValue::Array());
    cr_assert_eq(j[0], 12);
    cr_assert_eq(j[1], "test");
    cr_assert_eq(j[2], true);
    cr_assert_eq(j[3], nullptr);
    cr_assert_eq(j[4], json::JsonValue::Object());
    cr_assert_eq(j[5]["test"], 36);
    cr_assert_eq(j[6], json::JsonValue::Array());
    cr_assert_eq(j[7][0], 24);
    file.close();
}

Test(deserilizer_ifstream, json_empty_object)
{
    std::ifstream file("./test/source/direct/empty_object.json");
    json::JsonValue j;

    file >> j;
    cr_assert_eq(j, json::JsonValue::Object());
    file.close();
}

Test(deserilizer_ifstream, json_object)
{
    std::ifstream file("./test/source/direct/object.json");
    json::JsonValue j;

    file >> j;
    cr_assert_neq(j, json::JsonValue::Object());
    cr_assert_eq(j["testNumber"], 12);
    cr_assert_eq(j["testString"], "test");
    cr_assert_eq(j["testBool"], true);
    cr_assert_eq(j["testNull"], nullptr);
    cr_assert_eq(j["testArray"][0], 12);
    cr_assert_eq(j["testObject"]["test"], 24);
    file.close();
}