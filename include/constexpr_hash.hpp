#pragma once

#include <stdint.h>

namespace cexpr
{
    using hash_t = uint64_t;

    constexpr hash_t prime = 0x100000001B3ull;
    constexpr hash_t basis = 0xCBF29CE484222325ull;

    constexpr hash_t hash(const char* string, hash_t current_hash = basis)
    {
        return *string ? hash(string + 1, current_hash ^ (*string)*prime) : current_hash;
    }
}
