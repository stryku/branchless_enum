#pragma once

#include "branchless_helpers.hpp"

#include <tuple>
#include <type_traits>

namespace branchless
{
    template <typename ...types>
    struct variant
    {
        int value;

        template <typename T>
        constexpr static auto is_one_of_types = is_any_of_v<T, types...>;

        variant() = default;

        template <typename T,
                  typename = std::enable_if_t<is_one_of_types<T>>>
        variant(const T&)
            : value{ T::value }
        {}

        template <typename T,
                  typename = std::enable_if_t<is_one_of_types<T>>>
        variant& operator=(const T&)
        {
            value = T::value;
            return *this;
        }

        constexpr static variant fromValue(int value)
        {
            variant v;
            v.value = value;
            return v;
        }

        template <typename T,
                  typename = std::enable_if_t<is_one_of_types<T>>>
        bool operator==(const T&) const
        {
            return value == T::value;
        }

        bool operator==(const variant& other) const
        {
            return value == other.value;
        }
    };

    struct visit_impl
    {
        template <typename function, typename type, typename ...types>
        static void visit(int value, function &fun)
        {
            if (value == type::value) fun(type{});
            else visit<function, types...>(value, fun);
        }

        template <typename function, typename type, typename ...types>
        static void visit(int value, const function &fun)
        {
            if (value == type::value) fun(type{});
            else visit<function, types...>(value, fun);
        }

        template <typename function>
        static void visit(int value, function&)
        {}

        template <typename function>
        static void visit(int value, const function&)
        {}
    };

    template <typename ...types, typename visitor>
    void visit(variant<types...>& variant, visitor &v)
    {
        visit_impl::visit<visitor, types...>(variant.value, v);
    }

    template <typename ...types, typename visitor>
    void visit(variant<types...>& variant, const visitor &v)
    {
        visit_impl::visit<visitor, types...>(variant.value, v);
    }

    template <typename ...types, typename visitor>
    void visit(const variant<types...>& variant, visitor &v)
    {
        visit_impl::visit<visitor, types...>(variant.value, v);
    }

    template <typename ...types, typename visitor>
    void visit(const variant<types...>& variant, const visitor &v)
    {
        visit_impl::visit<visitor, types...>(variant.value, v);
    }
}