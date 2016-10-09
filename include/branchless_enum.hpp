#pragma once

#include "branchless_helpers.hpp"
#include "branchless_macros.hpp"

#include <boost/variant.hpp>

#define branchless_enum_impl(name, start_value, operators, count, ...) EVAL(PRIMITIVE_CAT(branchless_enum_, count)(name, start_value, operators, __VA_ARGS__))

#define branchless_enum(name, ...)  branchless_enum_impl(name, 0, 1, EVAL(BOOST_PP_VARIADIC_SIZE(__VA_ARGS__)), __VA_ARGS__)

#define branchless_enum_value(name, start_value,  ...)  branchless_enum_impl(name, start_value, 1, EVAL(BOOST_PP_VARIADIC_SIZE(__VA_ARGS__)), __VA_ARGS__)

#define branchless_enum_in_class(name, ...) branchless_enum_impl(name, 0, 0, EVAL(BOOST_PP_VARIADIC_SIZE(__VA_ARGS__)), __VA_ARGS__)

#define branchless_enum_in_class_value(name, start_value, ...) branchless_enum_impl(name, start_value, 0, EVAL(BOOST_PP_VARIADIC_SIZE(__VA_ARGS__)), __VA_ARGS__)
