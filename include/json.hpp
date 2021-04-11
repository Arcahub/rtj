
#if !defined(JZON)
#define JZON

#include <cinttypes>
#include <fstream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace json {

class JsonValue {
public:
    typedef std::nullptr_t Null;
    typedef std::unordered_map<std::string, JsonValue> Object;
    typedef std::vector<JsonValue> Array;
    typedef std::string String;
    typedef double Number;
    typedef bool Boolean;

    enum Type {
        NUL,
        OBJECT,
        ARRAY,
        STRING,
        BOOLEAN,
        NUMBER,
    };

    JsonValue()
        : JsonValue(nullptr)
    {
    }

    JsonValue(const JsonValue& other)
        : JsonValue()
    {
        *this = other;
    }

    JsonValue(Null)
        : m_tag(NUL)
    {
    }

    JsonValue(Boolean v) noexcept
        : m_tag(BOOLEAN)
        , m_bool(v)
    {
    }

    JsonValue(Number v) noexcept
        : m_tag(NUMBER)
        , m_num(v)
    {
    }

    JsonValue(int v) noexcept
        : JsonValue(double(v))
    {
    }

    JsonValue(Array v)
        : m_tag(ARRAY)
    {
        m_arr = new Array(v);
    }

    JsonValue(Object v)
        : m_tag(OBJECT)
    {
        m_obj = new Object(v);
    }

    JsonValue(String v)
        : m_tag(STRING)
        , m_str(v)
    {
    }

    JsonValue(const char* v)
        : m_tag(STRING)
        , m_str(v)
    {
    }

    ~JsonValue();

    Type getTag() const;

    std::string serialize() const;

    JsonValue& operator=(const JsonValue& other);

    JsonValue& operator[](size_t);
    const JsonValue& operator[](size_t) const;

    JsonValue& operator[](const std::string&);
    const JsonValue& operator[](const std::string&) const;

    operator Null() const;
    operator String() const;
    operator Boolean() const;
    operator Number() const;
    operator Object*() const;
    operator Array*() const;

    bool operator==(const JsonValue&) const;
    bool operator==(const Null&) const;
    bool operator==(const String&) const;
    bool operator==(const char* other) const;
    bool operator==(const Boolean&) const;
    bool operator==(const int&) const;
    bool operator==(const float&) const;
    bool operator==(const Number&) const;
    bool operator==(const Object&) const;
    bool operator==(const Array&) const;

    bool operator!=(const JsonValue&) const;
    bool operator!=(const Null&) const;
    bool operator!=(const String&) const;
    bool operator!=(const char* other) const;
    bool operator!=(const Boolean&) const;
    bool operator!=(const int&) const;
    bool operator!=(const float&) const;
    bool operator!=(const Number&) const;
    bool operator!=(const Object&) const;
    bool operator!=(const Array&) const;

    JsonValue& operator+=(const JsonValue& other);

private:
    Type m_tag;

    union {
        Boolean m_bool;
        Number m_num;
        String m_str;
        Array* m_arr;
        Object* m_obj;
    };
};

std::istream& operator>>(std::istream& is, JsonValue&);
std::ostream& operator<<(std::ostream& os, const JsonValue&);
}

json::JsonValue operator""_json(const char* str, size_t size);

#endif // JZON
