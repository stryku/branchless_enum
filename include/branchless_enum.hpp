#pragma once

#include "helpers.hpp"
#include "branchless_macos.hpp"

#include <boost/variant.hpp>

#define branchless_enum_variadic(name, start_value, count, ...) EVAL(PRIMITIVE_CAT(branchless_enum_, count)(name, start_value, __VA_ARGS__))

#define branchless_enum(name,  ...)  branchless_enum_variadic(name, 0, EVAL(BOOST_PP_VARIADIC_SIZE(__VA_ARGS__)), __VA_ARGS__)