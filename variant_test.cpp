#include "include/branchless_variant.hpp"

#include <iostream>

struct A
{
    constexpr static int value = 0;
};

struct B
{
    constexpr static int value = 1;
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

int main()
{
    branchless_variant<A, B> bv;

    std::cout << bv.value << "\n";

    bv = A{};
    std::cout << bv.value << "\n";

    bv = B{};
    std::cout << bv.value << "\n";

    my_visitor visitor;

    visit(bv, visitor);

    return 0;
}