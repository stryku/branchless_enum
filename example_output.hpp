#pragma once

struct be
{
    struct Types
    {
        constexpr static int start = -40 - 1;
        struct name_1
        {
            constexpr static int value = start + 1;
            constexpr static auto toString()
            {
                return "n1";
            }
        };
        struct name_2
        {
            constexpr static int value = start + 2;
            constexpr static auto toString()
            {
                return "n2";
            }
        };
    };
    static Types::name_1 name_1;
    static Types::name_2 name_2;
    using Type = boost::variant<Types::name_1, Types::name_2>;
    template <typename T>
    constexpr static bool is_this_type_v = is_any_of_v<T, Types::name_1, Types::name_2>;
    struct detail
    {
        struct value_visitor : public boost::static_visitor<int>
        {
            constexpr int operator()(be::Types::name_1) const
            {
                return be::Types::name_1::value;
            }
            constexpr int operator()(be::Types::name_2) const
            {
                return be::Types::name_2::value;
            }
        };
        template <typename T>
        static constexpr int value(T)
        {
            return T::value;
        }
        static int value(const Type& t)
        {
            return boost::apply_visitor(value_visitor{}, t);
        }
    };
    template <typename T>
    static constexpr auto toString(T)
    {
        return T::toString();
    }
    static auto toString(const Type& t)
    {
        return boost::apply_visitor(
            [](const auto& val)
        {
            return val.toString();
        },
            t);
    }
    static Type fromString(const std::string& str)
    {
        if (str == Types::name_1::toString())
            return Types::name_1{};
        if (str == Types::name_2::toString())
            return Types::name_2{};
        return{};
    }
};
template <typename T, typename T2,
    typename = std::enable_if<be::is_this_type_v<T> || be::is_this_type_v<T2>>>
    constexpr bool operator==(const T&, const T2&)
{
    return false;
}
template <typename T, typename = std::enable_if_t<be::is_this_type_v<T>>>
constexpr bool operator==(const T&, const T&)
{
    return true;
};
