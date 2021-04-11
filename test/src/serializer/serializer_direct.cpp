#include <criterion/criterion.h>
#include <iostream>

#include "json.hpp"

Test(serializer_direct, null)
{
    json::JsonValue j(nullptr);

    cr_assert_eq(j.serialize(), "null");
}

Test(serializer_direct, boolean_true)
{
    json::JsonValue j(true);

    cr_assert_eq(j.serialize(), "true");
}

Test(serializer_direct, boolean_false)
{
    json::JsonValue j(false);

    cr_assert_eq(j.serialize(), "false");
}

Test(serializer_direct, empty_string)
{
    json::JsonValue j("");

    cr_assert_eq(j.serialize(), "\"\"");
}

Test(serializer_direct, string)
{
    json::JsonValue j("test");

    cr_assert_eq(j.serialize(), "\"test\"");
}

Test(serializer_direct, number_int)
{
    json::JsonValue j(5);

    cr_assert_eq(j.serialize(), "5.000000");
}

Test(serializer_direct, number_zero)
{
    json::JsonValue j(0);

    cr_assert_eq(j.serialize(), "0.000000");
}

Test(serializer_direct, number_float)
{
    json::JsonValue j(3.14);

    cr_assert_eq(j.serialize(), "3.140000");
}

Test(serializer_direct, empty_array)
{
    json::JsonValue j = json::JsonValue::Array();

    cr_assert_eq(j.serialize(), "[]");
}

Test(serializer_direct, array)
{
    json::JsonValue j = json::JsonValue::Array();

    j[0] = 12;
    j[1] = "test";
    j[2] = true;
    j[3] = nullptr;
    j[4] = json::JsonValue::Object();
    j[5] = json::JsonValue::Object();
    j[5]["test"] = 36;
    j[6] = json::JsonValue::Array();
    j[7] = json::JsonValue::Array();
    j[7][0] = 24;
    cr_assert_eq(j.serialize(), "[12.000000,\"test\",true,null,{},{\"test\":36.000000},[],[24.000000]]");
}

Test(serializer_direct, empty_object)
{
    json::JsonValue j = json::JsonValue::Object();

    cr_assert_eq(j.serialize(), "{}");
}

Test(serializer_direct, object)
{
    json::JsonValue j = json::JsonValue::Object();

    j["testObject"] = json::JsonValue::Object();
    j["testObject"]["test"] = 24;
    j["testArray"] = json::JsonValue::Array();
    j["testArray"][0] = 12;
    j["testNull"] = nullptr;
    j["testBool"] = true;
    j["testString"] = "test";
    j["testNumber"] = 12;
    std::cout << j.serialize() << std::endl;
    cr_assert_eq(j.serialize(), "{\"testNumber\":12.000000,\"testString\":\"test\",\"testBool\":true,\"testNull\":null,\"testArray\":[12.000000],\"testObject\":{\"test\":24.000000}}");
}