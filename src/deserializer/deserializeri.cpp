#include "rtj/json.hpp"
#include <iostream>
#include <iterator>
#include <sstream>

static json::JsonValue getValue(std::istream& is);

static void jsonTrim(std::istream& is)
{
    while (is.peek() == ' ' || is.peek() == '\t' || is.peek() == '\n') {
        is.get();
    }
}

static std::string getKey(std::istream& is)
{
    std::string key;

    if (is.peek() != '"')
        throw std::exception();
    is.get();
    while (!is.eof() && is.peek() != '"')
        key += is.get();
    if (is.eof())
        throw std::exception();
    else
        is.get();
    return key;
}

json::JsonValue getObjectS(std::istream& is)
{
    json::JsonValue val = json::JsonValue::Object();
    std::string key;

    is.get();
    while (!is.eof() && is.peek() != '}') {
        jsonTrim(is);
        key = getKey(is);
        jsonTrim(is);
        if (is.peek() != ':')
            throw std::exception();
        is.get();
        jsonTrim(is);
        val[key] = getValue(is);
        jsonTrim(is);
        if (is.peek() == ',') {
            is.get();
            if (is.peek() == '}')
                throw std::exception();
        }
        jsonTrim(is);
    }
    if (is.eof())
        throw std::exception();
    else
        is.get();
    return val;
}

json::JsonValue getArrayS(std::istream& is)
{
    json::JsonValue val = json::JsonValue::Array();
    size_t index = 0;

    is.get();
    while (!is.eof() && is.peek() != ']') {
        jsonTrim(is);
        val[index] = getValue(is);
        index++;
        jsonTrim(is);
        if (is.peek() == ',') {
            is.get();
            if (is.peek() == '}')
                throw std::exception();
        }
        jsonTrim(is);
    }
    if (is.eof())
        throw std::exception();
    else
        is.get();
    return val;
}

json::JsonValue getNumberS(std::istream& is)
{
    double val = 0;
    double temp = 0;
    int index = 1;

    while (is.peek() >= '0' && is.peek() <= '9') {
        val = val * 10 + (is.get() - '0');
    }
    if (is.peek() == '.') {
        is.get();
        while (is.peek() >= '0' && is.peek() <= '9') {
            temp = is.get() - '0';
            for (int i = 0; i < index; i++, temp /= 10)
                ;
            val = val + temp;
            index += 1;
        }
    }
    return json::JsonValue::Number(val);
}

json::JsonValue getBoolS(std::istream& is)
{
    std::string str;
    std::string t = "true";
    std::string f = "false";

    while (is.peek() >= 'a' && is.peek() <= 'z')
        str += is.get();
    if (str.compare("true") == 0) {
        return json::JsonValue::Boolean(true);
    } else if (str.compare("false") == 0) {
        return json::JsonValue::Boolean(false);
    }
    throw std::exception();
}

json::JsonValue getStringS(std::istream& is)
{
    std::string str;

    is.get();
    while (!is.eof() && is.peek() != '"') {
        str += is.get();
    }
    if (is.eof()) {
        throw std::exception();
    } else {
        is.get();
    }
    return json::JsonValue::String(str);
}

json::JsonValue getNullS(std::istream& is)
{
    std::string str;

    for (int i = 0; i < 4; i++)
        str += is.get();
    if (str.compare("null") == 0) {
        return json::JsonValue::Null();
    }
    throw std::exception();
}

static json::JsonValue getValue(std::istream& is)
{
    char c = is.peek();

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

std::istream& json::operator>>(std::istream& is, json::JsonValue& js)
{
    char c = 0;
    std::string input;

    jsonTrim(is);
    if (is.eof() || is.peek() == -1) {
        js = json::JsonValue::Null();
        return is;
    }
    if (js == nullptr) {
        c = is.peek();
        if (c == '[') {
            js = getArrayS(is);
            return is;
        } else if (c == '{') {
            js = getObjectS(is);
            return is;
        }
    }
    while (!is.eof()) {
        jsonTrim(is);
        c = is.peek();
        if (c == '{')
            js += getObjectS(is);
        else if (c == '[')
            js += getArrayS(is);
        else if (c >= '0' && c <= '9')
            js = getNumberS(is);
        else if (c == 'f' || c == 't')
            js = getBoolS(is);
        else if (c == '"')
            js = getStringS(is);
        else if (c == 'n')
            js = getNullS(is);
        else
            throw std::exception();
        jsonTrim(is);
    }
    return is;
}
