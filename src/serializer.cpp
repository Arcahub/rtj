#include "json.hpp"

static std::string serializeArray(json::JsonValue::Array *array)
{
    std::string out;
    size_t i = 0;

    out += "[";
    for (auto val : *array) {
        out += val.serialize();
        if (array->size() - 1 > i)
            out += ",";
        i++;
    }
    out += "]";
    return out;
}

static std::string serializeObject(json::JsonValue::Object *obj)
{
    std::string out;
    size_t i = 0;

    out += "{";
    for (auto val : *obj) {
        out += "\"" + val.first + "\"" + ":";
        out += val.second.serialize();
        if (obj->size() - 1 > i)
            out += ",";
        i++;
    }
    out += "}";
    return out;
}

std::string json::JsonValue::serialize() const
{
    switch (m_tag) {
        case STRING:
            return "\"" + m_str + "\"";
        case NUMBER:
            return std::to_string(m_num);
        case BOOLEAN:
            return m_bool ? "true" : "false";
        case NUL:
            return "null";
        case ARRAY:
            return serializeArray(m_arr);
        case OBJECT:
            return serializeObject(m_obj);
        default:
            return "";

    }
}

std::ostream& json::operator<<(std::ostream& os, const json::JsonValue&j)
{
    os << j.serialize();
    return os;
}