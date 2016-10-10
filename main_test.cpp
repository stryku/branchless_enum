#include <iostream>
#include <tuple>
#include <type_traits>
#include "include/branchless_enum.hpp"

//#include <boost/variant.hpp>
//
//template<bool...> struct bool_pack;
//
//template <bool ...bs>
//using all_true = std::is_same<bool_pack<bs..., true>, bool_pack<true, bs...>>;
//
//template <bool ...bs>
//using all_false = std::is_same<bool_pack<bs..., false>, bool_pack<false, bs...>>;
//
//template <bool ...bs>
//using any_true = std::integral_constant<bool, !all_false<bs...>::value>;
//
//template <typename T, typename ...Args>
//using is_any_of = any_true<std::is_same<T, Args>::value...>;
//
//template <typename T, typename ...Args>
//constexpr bool is_any_of_v = is_any_of<T, Args...>::value;

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

branchless_enum_value(be, -40, name_1, name_2)

struct Foo
{
    branchless_enum_in_class_value(be, -40, name_1, name_2)
};

struct BranchlessVisitor : public boost::static_visitor<>
{
public:
    void operator()(Foo::be::Types::name_1) const
    {
        std::cout << "hello t1\n";
    }
    void operator()(Foo::be::Types::name_2) const
    {
        std::cout << "hello t2\n";
    }

    template <typename T>
    void operator()(T) const
    {
        std::cout << "hello default\n";
    }
};

struct BenchmarkResult
{
    
};

//
//int main(int argc, char *argv[])
//{
//    auto magic = Magic::fromString(argv[1]);
//    auto branchless = Foo::be::fromString(argv[1]);
//    auto branchless2 = Foo::be::fromString(argv[2]);
//
//    auto constexp = Foo::be::name_1;
//    auto constexp2 = Foo::be::name_2;
//
//    std::cout << "magic\n";
//    foo(magic);
//
//    std::cout << "\n\nbranchless\n";
//    boost::apply_visitor(BranchlessVisitor{}, branchless);
//
//    if (constexp == -40)
//
//    std::cout << "\n\nconstexpr compare\n";
//    if (constexp == constexp2)
//        std::cout << Foo::be::toString(constexp) << " == " << Foo::be::toString(constexp2);
//    else
//        std::cout << Foo::be::toString(constexp) << " != " << Foo::be::toString(constexp2);
//
//    std::cout << "\n";
//    if (constexp == constexp)
//        std::cout << Foo::be::toString(constexp) << " == " << Foo::be::toString(constexp);
//    else
//        std::cout << Foo::be::toString(constexp) << " != " << Foo::be::toString(constexp);
//
//    std::cout << "\n\nbranchless compare\n";
//    if (branchless == branchless2)
//        std::cout << Foo::be::toString(branchless) << " == " << Foo::be::toString(branchless2);
//    else
//        std::cout << Foo::be::toString(branchless) << " != " << Foo::be::toString(branchless2);
//
//    std::cout << "\n\nvalue compare\n";
//    int value{ 100 };
//    if (Foo::be::name_1.value == value)
//        std::cout << Foo::be::name_1.toString() << ".value(" << Foo::be::name_1.value << ") == " << value;
//    else
//        std::cout << Foo::be::name_1.toString() << ".value(" << Foo::be::name_1.value << ") != " << value;
//
//    std::cout << "\n\nvalue compare\n";
//    int value2{ -39 };
//    if (Foo::be::name_2.value == value2)
//        std::cout << Foo::be::name_2.toString() << ".value(" << Foo::be::name_2.value << ") == " << value2;
//    else
//        std::cout << Foo::be::name_2.toString() << ".value(" << Foo::be::name_2.value << ") != " << value2;
//
//    std::cout << "\n\n";
//    return 0;
//}
