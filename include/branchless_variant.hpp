#pragma once

#include "branchless_helpers.hpp"

#include <tuple>
#include <type_traits>



template <typename ...types>
struct branchless_variant
{
    int value{ -1 };

    template <typename T>
    constexpr static auto is_one_of_types = is_any_of_v<T, types...>;

    branchless_variant() = default;

    template <typename T,
              typename = std::enable_if_t<is_one_of_types<T>>>
    branchless_variant(const T&)
        : value{ T::value }
    {}

    template <typename T,
              typename = std::enable_if_t<is_one_of_types<T>>>
    branchless_variant& operator=(const T&)
    {
        value = T::value;
        return *this;
    }

    template <typename T,
              typename = std::enable_if_t<is_one_of_types<T>>>
    bool operator==(const T&)
    {
        return value == T::value;
    }

    bool operator==(const branchless_variant& other)
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

    template <typename function>
    static void visit(int value, function&)
    {}
};

template <typename ...types, typename visitor>
void visit(branchless_variant<types...>& variant, visitor &v)
{
    visit_impl::visit<visitor, types...>(variant.value, v);
}

template <typename ...types, typename visitor>
void visit(branchless_variant<types...>& variant, const visitor &v)
{
    visit_impl::visit<visitor, types...>(variant.value, v);
}