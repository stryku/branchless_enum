#pragma once

#include "helpers.hpp"

#include <boost/variant.hpp>


#define branchless_enum_2(name, start_value, n1, n2)                                      \
struct name                                      \
{                                      \
    struct Types                                      \
    {                                      \
        constexpr static int start = start_value;                                      \
        struct n1                                      \
        {                                      \
            constexpr static int value = start + 0;                                      \
            constexpr static auto toString() { return "n1"; }                                      \
        };                                      \
        struct n2                                      \
        {                                      \
            constexpr static int value = start + 1;                                      \
            constexpr static auto toString() { return "n2"; }                                      \
        };                                      \
    };                                      \
    static Types::n1 n1;                                      \
    static Types::n2 n2;                                      \
    using Type = boost::variant<Types::n1, Types::n2>;                                      \
    template <typename T>                                      \
    constexpr static bool is_this_type_v = is_any_of_v<T, Types::n1, Types::n2>;                                      \
    struct detail                                      \
    {                                      \
        struct value_visitor : public boost::static_visitor<int>                                      \
        {                                      \
        public:                                      \
            constexpr int operator()(name::Types::n1) const                                      \
            {                                      \
                return name::Types::n1::value;                                      \
            }                                      \
            constexpr int operator()(name::Types::n2) const                                      \
            {                                      \
                return name::Types::n2::value;                                      \
            }                                      \
        };                                      \
        template <typename T>                                      \
        static constexpr int value(T)                                      \
        {                                      \
            return T::value;                                      \
        }                                      \
                                                                                \
        static int value(const Type &t)                                      \
        {                                      \
            return boost::apply_visitor(value_visitor{}, t);                                      \
        }                                      \
    };                                      \
    template <typename T>                                      \
    static constexpr auto toString(T)                                      \
    {                                      \
        return T::toString();                                      \
    }                                      \
    static auto toString(const Type &t)                                      \
    {                                      \
        return boost::apply_visitor([](const auto &val) { return val.toString(); }, \
                                    t);                                      \
    }                                      \
    static Type fromString(const std::string &str)\
    {                               \
        if (str == Types::n1::toString())  return Types::n1{};                               \
        if (str == Types::n2::toString())  return Types::n2{};                               \
                                       \
        return{};                               \
    }                               \
};                               \
template <typename T, typename T2, \
    typename = std::enable_if<name::is_this_type_v<T> || \
    name::is_this_type_v<T2>>>                               \
    constexpr bool operator==(const T&, const T2&)                               \
{                               \
    return false;                                      \
}                                      \
template <typename T, \
    typename = std::enable_if_t<name::is_this_type_v<T>>>                                      \
    constexpr bool operator==(const T&, const T&)                                      \
{                                      \
    return true;                                      \
}                                      


#define branchless_enum_variadic(name, start_value, count, ...) EVAL(PRIMITIVE_CAT(branchless_enum_, count)(name, start_value, __VA_ARGS__))

#define branchless_enum(name,  ...)  branchless_enum_variadic(name, 0, EVAL(BOOST_PP_VARIADIC_SIZE(__VA_ARGS__)), __VA_ARGS__)