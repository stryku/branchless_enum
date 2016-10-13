#pragma once

#include "include/branchless_variant.hpp"
#include "include/constexpr_hash.hpp"
#include "include/cexpr_sort.hpp"

#include <cexpr/array.hpp>
#include <cexpr/algorithm.hpp>
#include <cexpr/crypto.hpp>

template <typename ...types>
constexpr auto getArray() ->cexpr::array<const char*, sizeof...(types)>
{
    return { (types::toString())... };
}

struct type_name_info
{
    int value;
    cexpr::detail::hash_t hash;

    constexpr bool operator==(const type_name_info& other) const
    {
        return hash == other.hash;
    }
};


template <typename ...types>
constexpr auto getHashes()
          ->cexpr::array<type_name_info, sizeof...(types)>
{
    return{ { types::value, cexpr::hash(types::toString())}... };
}

template <typename ...types>
constexpr const auto getSortedHashes()
          ->cexpr::array<type_name_info, sizeof...(types)>
{
    constexpr const auto hashes = getHashes<types...>();
    return cexpr::sort(hashes);
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
    constexpr static const auto hashes = getSortedHashes<be_namespace::Types::name_1, be_namespace::Types::name_2>();

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
        type_name_info info{ 0, cexpr::hash(str.c_str()) };

        auto index = cexpr::binary_search(hashes, info);
        return Type::fromValue(hashes[index].value);

        //if (str == be_namespace::Types::name_1::toString()) return be_namespace::Types::name_1{};
        //if (str == be_namespace::Types::name_2::toString()) return be_namespace::Types::name_2{};

        //return{};
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
