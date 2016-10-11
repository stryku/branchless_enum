#include "include/branchless_variant.hpp"
//#include "example_output.hpp"
#include "include/branchless_enum.hpp"
#include "branch_enum.hpp"

#include <iostream>

struct A
{
    constexpr static int value = 0;
    constexpr static auto toString() { return "A"; }
};

struct B
{
    constexpr static int value = 1;
    constexpr static auto toString() { return "B"; }
};



class my_visitor
{
public:
    void operator()(const A&) const
    {
        std::cout << A::value;
    }

    void operator()(const B&) const
    {
        std::cout << B::value;
    }
};

int count;


branchless_enum(be, name_1, name_2);

struct branchless_function
{
public:
    using return_type = void;

    return_type operator()(const be::Types::name_1&)
    {
        ++count;
    }

    return_type operator()(const be::Types::name_2&)
    {
        --count;
    }
    
    template <typename ...T>
    return_type operator()(T...) {}
};



void branch_function(branch::Types type)
{
    switch (type)
    {
    case branch::Types::name_1: ++count;
        break;
    case branch::Types::name_2: --count;
        break;

    default:
        break;
    }
}

int main(int argc, char *argv[])
{
    branchless::variant<A, B> bv;
    std::cout << bv.value << "\n";
    bv = A{};
    std::cout << bv.value << "\n";
    bv = B{};
    std::cout << bv.value << "\n";
    my_visitor visitor;
    visit(bv, visitor);


    std::cout << "explicit_type toString: ";
    const auto explicit_type = be::name_1;
    std::cout << be::toString(explicit_type) << "\n";

    std::cout << "variant_type toString: ";
    const be::Type variant_type = explicit_type;
    std::cout << be::toString(variant_type) << "\n";

    std::cout << "constexpr compare:";
    if (be::name_1 == be::name_2)
        std::cout << be::name_1.toString() << " == " << be::name_2.toString() << "\n";
    else
        std::cout << be::name_1.toString() << " != " << be::name_2.toString() << "\n";

    std::cout << "constexpr compare: ";
    if (be::name_2 == be::name_2)
        std::cout << be::name_2.toString() << " == " << be::name_2.toString() << "\n";
    else
        std::cout << be::name_2.toString() << " != " << be::name_2.toString() << "\n";


    std::cout << "variant compare: ";
    if (variant_type == be::name_1)
        std::cout << be::name_1.toString() << " == " << be::toString(variant_type) << "\n";
    else
        std::cout << be::name_1.toString() << " != " << be::toString(variant_type) << "\n";

    const be::Type variant_type_2 = be::name_2;
    std::cout << "variant compare: ";
    if (variant_type == variant_type_2)
        std::cout << be::toString(variant_type) << " == " << be::toString(variant_type_2) << "\n";
    else
        std::cout << be::toString(variant_type) << " != " << be::toString(variant_type_2) << "\n";

    std::cout << "branchless_function: ";
    branchless_function f;
    branchless::visit(variant_type_2, f);
    std::cout << count << "\n";

    count = 0;

    std::cout << "branch_function: ";
    branch_function(argc > 1 ? branch::Types::name_1 : branch::Types::name_2);
    std::cout << count << "\n";

    std::cout << "sizeof(variant) == " << sizeof(branchless::variant<A, B>) << "\n";;
    std::cout << "sizeof(enum) == " << sizeof(branch::Types) << "\n";

    return 0;
}