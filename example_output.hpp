#pragma once

#include "include/branchless_variant.hpp"

#include <array>

template <typename ...Types>
constexpr auto getArray() -> std::array<const char*, sizeof...(Types)>
{
    return { (Types::toString())... };
}

struct be_namespace
{
    struct Types
    {
        struct name_1; struct name_2;

        template <typename T>
        constexpr static bool is_this_type_v = is_any_of_v<T, name_1, name_2>;

        constexpr static int start = 0;
        struct name_1
        {
            constexpr static int value = start + 0;
            constexpr static auto toString()
            {
                return "n1";
            }

            constexpr bool operator==(const name_1&)
            {
                return true;
            }


            template <typename T, typename = std::enable_if_t<is_this_type_v<T>>>
            constexpr bool operator==(const T&)
            {
                return false;
            }
        };
        struct name_2
        {
            constexpr static int value = start + 1;
            constexpr static auto toString()
            {
                return "n2";
            }

            constexpr bool operator==(const name_2&)
            {
                return true;
            }

            template <typename T, typename = std::enable_if_t<is_this_type_v<T>>>
            constexpr bool operator==(const T&)
            {
                return false;
            }
        };
    };
};

struct be
{
    struct Types
    {
        using name_1 = be_namespace::Types::name_1;
        using name_2 = be_namespace::Types::name_2;
    };
    constexpr static Types::name_1 name_1{};
    constexpr static Types::name_2 name_2{};
    using Type = branchless::variant<be_namespace::Types::name_1, be_namespace::Types::name_2>;

    constexpr static const auto nameArray = getArray<be_namespace::Types::name_1, be_namespace::Types::name_2>();

    struct detail
    {
        struct value_visitor 
        {
            constexpr int operator()(be_namespace::Types::name_1) const
            {
                return be_namespace::Types::name_1::value;
            }
            constexpr int operator()(be_namespace::Types::name_2) const
            {
                return be_namespace::Types::name_2::value;
            }
        };
        template <typename T,
                  typename = std::enable_if_t<be_namespace::Types::is_this_type_v<T>>>
        static constexpr int value(T)
        {
            return T::value;
        }
        static int value(const Type& t)
        {
            return t.value;
        }
    };
    template <typename T,
              typename = std::enable_if_t<be_namespace::Types::is_this_type_v<T>>>
    static constexpr auto toString(T)
    {
        return T::toString();
    }
    static auto toString(const Type& t)
    {
        return nameArray[t.value];
    }

    static Type fromString(const std::string& str)
    {
        if (str == be_namespace::Types::name_1::toString()) return be_namespace::Types::name_1{};
        if (str == be_namespace::Types::name_2::toString()) return be_namespace::Types::name_2{};

        return{};
    }
};
//template <typename T, typename T2,
//    typename = std::enable_if<be::is_this_type_v<T> || be::is_this_type_v<T2>>>
//    constexpr bool operator==(const T&, const T2&)
//{
//    return false;
//}
//template <typename T, typename = std::enable_if_t<be::is_this_type_v<T>>>
//constexpr bool operator==(const T&, const T&)
//{
//    return true;
//};
