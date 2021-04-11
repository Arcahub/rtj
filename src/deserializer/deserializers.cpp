#include "rtj/json.hpp"
#include <iostream>
#include <iterator>
#include <sstream>

static json::JsonValue getValue(std::string& is);

static void jsonTrim(std::string& is)
{
    while (is[0] == ' ' || is[0] == '\t' || is[0] == '\n') {
        is.erase(0, 1);
    }
}

static std::string getKey(std::string& is)
{
    std::string key;

    if (is[0] != '"')
        throw std::exception();
    is.erase(0, 1);
    while (!is.empty() && is[0] != '"') {
        key += is[0];
        is.erase(0, 1);
    }
    if (is.empty())
        throw std::exception();
    else
        is.erase(0, 1);
    return key;
}

static json::JsonValue getObjectS(std::string& is)
{
    json::JsonValue val = json::JsonValue::Object();
    std::string key;

    is.erase(0, 1);
    while (!is.empty() && is[0] != '}') {
        jsonTrim(is);
        key = getKey(is);
        jsonTrim(is);
        if (is[0] != ':')
            throw std::exception();
        is.erase(0, 1);
        jsonTrim(is);
        val[key] = getValue(is);
        jsonTrim(is);
        if (is[0] == ',') {
            is.erase(0, 1);
            if (is[0] == '}')
                throw std::exception();
        }
        jsonTrim(is);
    }
    if (is.empty())
        throw std::exception();
    else
        is.erase(0, 1);
    return val;
}

static json::JsonValue getArrayS(std::string& is)
{
    json::JsonValue val = json::JsonValue::Array();
    size_t index = 0;

    is.erase(0, 1);
    while (!is.empty() && is[0] != ']') {
        jsonTrim(is);
        val[index] = getValue(is);
        index++;
        jsonTrim(is);
        if (is[0] == ',') {
            is.erase(0, 1);
            if (is[0] == '}')
                throw std::exception();
        }
        jsonTrim(is);
    }
    if (is.empty())
        throw std::exception();
    else
        is.erase(0, 1);
    return val;
}

static json::JsonValue getNumberS(std::string& is)
{
    double val = 0;
    double temp = 0;
    int index = 1;

    while (is[0] >= '0' && is[0] <= '9') {
        val = val * 10 + (is[0] - '0');
        is.erase(0, 1);
    }
    if (is[0] == '.') {
        is.erase(0, 1);
        while (is[0] >= '0' && is[0] <= '9') {
            temp = is[0] - '0';
            is.erase(0, 1);
            for (int i = 0; i < index; i++, temp /= 10)
                ;
            val = val + temp;
            index += 1;
        }
    }
    return json::JsonValue::Number(val);
}

static json::JsonValue getBoolS(std::string& is)
{
    std::string str;
    std::string t = "true";
    std::string f = "false";

    while (is[0] >= 'a' && is[0] <= 'z') {
        str += is[0];
        is.erase(0, 1);
    }
    if (str.compare("true") == 0) {
        return json::JsonValue::Boolean(true);
    } else if (str.compare("false") == 0) {
        return json::JsonValue::Boolean(false);
    }
    throw std::exception();
}

static json::JsonValue getStringS(std::string& is)
{
    std::string str;

    is.erase(0, 1);
    while (!is.empty() && is[0] != '"') {
        str += is[0];
        is.erase(0, 1);
    }
    if (is.empty()) {
        throw std::exception();
    } else {
        is.erase(0, 1);
    }
    return json::JsonValue::String(str);
}

static json::JsonValue getNullS(std::string& is)
{
    std::string str;

    for (int i = 0; i < 4; i++) {
        str += is[0];
        is.erase(0, 1);
    }
    if (str.compare("null") == 0) {
        return json::JsonValue::Null();
    }
    throw std::exception();
}

static json::JsonValue getValue(std::string& is)
{
    char c = is[0];

    if (c == '{')
        return getObjectS(is);
    else if (c == '[')
        return getArrayS(is);
    else if (c >= '0' && c <= '9')
        return getNumberS(is);
    else if (c == 'f' || c == 't')
        return getBoolS(is);
    else if (c == '"')
        return getStringS(is);
    else if (c == 'n')
        return getNullS(is);
    else
        throw std::exception();
}

json::JsonValue operator""_json(const char* str, size_t size)
{
    char c = 0;
    std::string s(str, size);

    if (s.empty())
        return json::JsonValue::Null();
    jsonTrim(s);
    while (!s.empty()) {
        jsonTrim(s);
        c = s[0];
        if (c == '{')
            return getObjectS(s);
        else if (c == '[')
            return getArrayS(s);
        else if (c >= '0' && c <= '9')
            return getNumberS(s);
        else if (c == 'f' || c == 't')
            return getBoolS(s);
        else if (c == '"')
            return getStringS(s);
        else if (c == 'n')
            return getNullS(s);
        else
            throw std::exception();
        jsonTrim(s);
    }
    return json::JsonValue::Null();
}
