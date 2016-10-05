#include <iostream>
#include <tuple>
#include <type_traits>

#include <boost/variant.hpp>

template<bool...> struct bool_pack;

template <bool ...bs>
using all_true = std::is_same<bool_pack<bs..., true>, bool_pack<true, bs...>>;

template <bool ...bs>
using all_false = std::is_same<bool_pack<bs..., false>, bool_pack<false, bs...>>;

template <bool ...bs>
using any_true = std::integral_constant<bool, !all_false<bs...>::value>;

template <typename T, typename ...Args>
using is_any_of = any_true<std::is_same<T, Args>::value...>;

template <typename T, typename ...Args>
constexpr bool is_any_of_v = is_any_of<T, Args...>::value;

namespace Magic
{
    enum class Type
    {
        t1,
        t2
    };

    constexpr auto toString(Type type)
    {
        return type == Type::t1 ? "t1" :
            type == Type::t2 ? "t2" : "unknow";
    }

    Type fromString(const std::string &str)
    {
        if (str == "t1") return Type::t1;
        if (str == "t2") return Type::t2;
    }
}

void foo(Magic::Type type)
{
    switch (type)
    {
    case Magic::Type::t1: std::cout << "hello t1\n";
        break;
    case Magic::Type::t2: std::cout << "hello t2\n";
        break;
    default:
        std::cout << "hello default\n";
        break;
    }
}


struct Branchless
{
    struct Types
    {
        constexpr static int start = 11;
        struct t1
        {
            constexpr static int value = start + 0;
            constexpr static auto toString() { return "t1"; }
        };
        struct t2
        {
            constexpr static int value = start + 1;
            constexpr static auto toString() { return "t2"; }
        };
    };

    static Types::t1 t1;
    static Types::t2 t2;

    using Type = boost::variant<Types::t1, Types::t2>;

    template <typename T>
    constexpr static bool is_this_type_v = is_any_of_v<T, Types::t1, Types::t2>;

    struct detail
    {
        struct value_visitor : public boost::static_visitor<int>
        {
        public:
            constexpr int operator()(Branchless::Types::t1) const
            {
                return Branchless::Types::t1::value;
            }
            constexpr int operator()(Branchless::Types::t2) const
            {
                return Branchless::Types::t2::value;
            }
        };

        template <typename T>
        static constexpr int value(T)
        {
            return T::value;
        }

        static int value(const Type &t)
        {
            return boost::apply_visitor(value_visitor{}, t);
        }
    };

    template <typename T>
    static constexpr auto toString(T)
    {
        return T::toString();
    }

    static auto toString(const Type &t)
    {
        return boost::apply_visitor([](auto val) { return val.toString(); },
                                    t);
    }

    static Type fromString(const std::string &str)
    {
        if (str == Types::t1::toString())  return Types::t1{};
        if (str == Types::t2::toString())  return Types::t2{};

        return{};
    }
};

template <typename T, typename T2,
          typename = std::enable_if<Branchless::is_this_type_v<T> || 
                                    Branchless::is_this_type_v<T2>
                                    
    >>
constexpr bool operator==(const T&, const T2&)
{
    return false;
}

template <typename T,
          typename = std::enable_if_t<Branchless::is_this_type_v<T>>>
constexpr bool operator==(const T&, const T&)
{
    return true;
}

struct BranchlessVisitor : public boost::static_visitor<>
{
public:
    void operator()(Branchless::Types::t1) const
    {
        std::cout << "hello t1\n";
    }
    void operator()(Branchless::Types::t2) const
    {
        std::cout << "hello t2\n";
    }

    template <typename T>
    void operator()(T) const
    {
        std::cout << "hello default\n";
    }
};

int main(int argc, char *argv[])
{
    auto magic = Magic::fromString(argv[1]);
    auto branchless = Branchless::fromString(argv[1]);
    auto branchless2 = Branchless::fromString(argv[2]);

    auto constexp = Branchless::t1;
    auto constexp2 = Branchless::t2;

    std::cout << "magic\n";
    foo(magic);

    std::cout << "\n\nbranchless\n";
    boost::apply_visitor(BranchlessVisitor{}, branchless);

    std::cout << "\n\nconstexpr compare\n";
    if (constexp == constexp2)
        std::cout << Branchless::toString(constexp) << " == " << Branchless::toString(constexp2);
    else
        std::cout << Branchless::toString(constexp) << " != " << Branchless::toString(constexp2);

    std::cout << "\n";
    if (constexp == constexp)
        std::cout << Branchless::toString(constexp) << " == " << Branchless::toString(constexp);
    else
        std::cout << Branchless::toString(constexp) << " != " << Branchless::toString(constexp);

    std::cout << "\n\nbranchless compare\n";
    if (branchless == branchless2)
        std::cout << Branchless::toString(branchless) << " == " << Branchless::toString(branchless2);
    else
        std::cout << Branchless::toString(branchless) << " != " << Branchless::toString(branchless2);

    std::cout << "\n\n";
    return 0;
}