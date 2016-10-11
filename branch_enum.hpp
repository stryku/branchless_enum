#pragma once

#include <string>

namespace branch
{
    enum class Types
    {
        name_1,
        name_2
    };

    constexpr auto toString(Types type)
    {
        return type == Types::name_1 ? "name_1" :
            type == Types::name_2 ? "name_2" : "unknow";
    }

    Types fromString(const std::string &str)
    {
        if (str == "name_1") return Types::name_1;
        if (str == "name_2") return Types::name_2;
    }
}