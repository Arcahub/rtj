#include "json.hpp"
#include <iostream>

json::JsonValue::~JsonValue()
{
    switch (m_tag) {
    case Type::OBJECT:
        delete (m_obj);
        break;
    case Type::ARRAY:
        delete (m_arr);
        break;
    default:
        return;
    }
}

json::JsonValue::Type json::JsonValue::getTag() const
{
    return m_tag;
}

json::JsonValue& json::JsonValue::operator=(const JsonValue& other)
{
    if (m_tag != other.m_tag) {
        switch (m_tag) {
        case Type::OBJECT:
            delete (m_obj);
            break;
        case Type::ARRAY:
            delete (m_arr);
            break;
        case Type::STRING:
            delete (&m_str);
            break;
        default:
            break;
        }

        switch (other.m_tag) {
        case Type::OBJECT:
            m_obj = new Object(*other.m_obj);
            break;
        case Type::ARRAY:
            m_arr = new Array(*other.m_arr);
            break;
        case Type::STRING:
            new (&m_str) String(other.m_str);
            break;
        case Type::BOOLEAN:
            m_bool = other.m_bool;
            break;
        case Type::NUMBER:
            m_num = other.m_num;
            break;
        default:
            break;
        }
    } else {
        switch (m_tag) {
        case Type::OBJECT:
            m_obj = other.m_obj;
            break;
        case Type::ARRAY:
            m_arr = other.m_arr;
            break;
        case Type::STRING:
            m_str = other.m_str;
            break;
        case Type::BOOLEAN:
            m_bool = other.m_bool;
            break;
        case Type::NUMBER:
            m_num = other.m_num;
            break;
        default:
            break;
        }
    }

    m_tag = other.m_tag;

    return *this;
}

json::JsonValue& json::JsonValue::operator[](size_t i)
{
    if (m_tag != ARRAY)
        throw std::exception();
    if (i >= m_arr->size()) {
        m_arr->resize(i + 1);
    }
    return (*m_arr)[i];
}

const json::JsonValue& json::JsonValue::operator[](size_t i) const
{
    if (m_tag != ARRAY)
        throw std::exception();
    if (i >= m_arr->size()) {
        throw std::exception();
    }
    return (*m_arr)[i];
}

json::JsonValue& json::JsonValue::operator[](const std::string& key)
{
    if (m_tag != OBJECT)
        throw std::exception();
    return (*m_obj)[key];
}

const json::JsonValue& json::JsonValue::operator[](const std::string& key) const
{
    if (m_tag != OBJECT)
        throw std::exception();
    return m_obj->at(key);
}

json::JsonValue::operator Null() const
{
    return Null();
}

json::JsonValue::operator String() const
{
    if (m_tag == STRING)
        return m_str;
    return String();
}
json::JsonValue::operator Boolean() const
{
    if (m_tag == BOOLEAN)
        return m_bool;
    return Boolean();
}
json::JsonValue::operator Number() const
{
    if (m_tag == NUMBER)
        return m_num;
    return Number();
}
json::JsonValue::operator Object*() const
{
    if (m_tag == OBJECT)
        return m_obj;
    return new Object();
}
json::JsonValue::operator Array*() const
{
    if (m_tag == ARRAY)
        return m_arr;
    return new Array();
}

bool json::JsonValue::operator==(const JsonValue& other) const
{
    if (m_tag != other.m_tag)
        return false;
    switch (m_tag) {
    case NUL:
        return true;
    case OBJECT:
        return m_obj == other.m_obj;
    case ARRAY:
        return m_arr == other.m_arr;
    case STRING:
        return m_str.compare(other.m_str) == 0;
    case NUMBER:
        return m_num == other.m_num;
    case BOOLEAN:
        return m_bool == other.m_bool;
    }
    return false;
}

bool json::JsonValue::operator==(const Null&) const
{
    return m_tag == NUL;
}

bool json::JsonValue::operator==(const char* other) const
{
    return m_str.compare(other) == 0;
}

bool json::JsonValue::operator==(const String& other) const
{
    if (m_tag != STRING)
        return false;
    return m_str.compare(other) == 0;
}

bool json::JsonValue::operator==(const int& other) const
{
    return m_num == other;
}

bool json::JsonValue::operator==(const float& other) const
{
    return m_num == other;
}

bool json::JsonValue::operator==(const Number& other) const
{
    if (m_tag != NUMBER)
        return false;
    return m_num == other;
}

bool json::JsonValue::operator==(const Boolean& other) const
{
    if (m_tag != BOOLEAN)
        return false;
    return m_bool == other;
}

bool json::JsonValue::operator==(const Object& other) const
{
    if (m_tag != OBJECT)
        return false;
    return *m_obj == other;
}

bool json::JsonValue::operator==(const Array& other) const
{
    if (m_tag != ARRAY)
        return false;
    return *m_arr == other;
}

bool json::JsonValue::operator!=(const JsonValue& other) const
{
    if (m_tag != other.m_tag)
        return true;
    switch (m_tag) {
    case NUL:
        return true;
    case OBJECT:
        return m_obj != other.m_obj;
    case ARRAY:
        return m_arr != other.m_arr;
    case STRING:
        return m_str.compare(other.m_str) != 0;
    case NUMBER:
        return m_num != other.m_num;
    case BOOLEAN:
        return m_bool != other.m_bool;
    }
    return false;
}

bool json::JsonValue::operator!=(const Null&) const
{
    return m_tag != NUL;
}

bool json::JsonValue::operator!=(const char* other) const
{
    return m_str.compare(other) != 0;
}

bool json::JsonValue::operator!=(const String& other) const
{
    if (m_tag != STRING)
        return true;
    return m_str.compare(other) != 0;
}

bool json::JsonValue::operator!=(const int& other) const
{
    return m_num != other;
}

bool json::JsonValue::operator!=(const float& other) const
{
    return m_num != other;
}

bool json::JsonValue::operator!=(const Number& other) const
{
    if (m_tag != NUMBER)
        return true;
    return m_num != other;
}

bool json::JsonValue::operator!=(const Boolean& other) const
{
    if (m_tag != BOOLEAN)
        return true;
    return m_bool != other;
}

bool json::JsonValue::operator!=(const Object& other) const
{
    if (m_tag != OBJECT)
        return true;
    return *m_obj != other;
}

bool json::JsonValue::operator!=(const Array& other) const
{
    if (m_tag != ARRAY)
        return true;
    return *m_arr != other;
}

json::JsonValue& json::JsonValue::operator+=(const JsonValue& other)
{
    if (m_tag == OBJECT && other.m_tag == OBJECT) {
        m_obj->insert(other.m_obj->begin(), other.m_obj->end());
    } else if (m_tag == ARRAY && other.m_tag == ARRAY) {
        m_arr->insert(m_arr->begin(), other.m_arr->begin(), other.m_arr->end());
    } else if (m_tag == ARRAY) {
        m_arr->push_back(other);
    } else {
        throw std::exception();
    }
    return *this;
}