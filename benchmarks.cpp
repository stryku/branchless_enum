#include "include/branchless_enum.hpp"

#include <chrono>
#include <vector>
#include <iostream>
#include <random>

branchless_enum(branchless,
                name_1,
                name_2,
                name_3,
                name_4,
                name_5,
                name_6,
                name_7,
                name_8,
                name_9,
                name_10,
                name_11,
                name_12,
                name_13,
                name_14,
                name_15,
                name_16,
                name_17,
                name_18,
                name_19);


template <typename Clock>
struct BenchmarkResult
{
    struct Duration
    {
        using tp = std::chrono::time_point<Clock>;

        tp start;
        tp finnish;
    };

    Duration create;
    Duration fill;
    Duration fromString;
    Duration toString;
    Duration function;

    static auto elapsed(const Duration &d)
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(d.finnish - d.start);
    }
};

#pragma optimize( "", off )
struct BranchlessFunction : public boost::static_visitor<>
{
public:
    void operator()(branchless::Types::name_1) const {}
    void operator()(branchless::Types::name_2) const {}
    void operator()(branchless::Types::name_3) const {}
    void operator()(branchless::Types::name_4) const {}
    void operator()(branchless::Types::name_5) const {}
    void operator()(branchless::Types::name_6) const {}
    void operator()(branchless::Types::name_7) const {}
    void operator()(branchless::Types::name_8) const {}
    void operator()(branchless::Types::name_9) const {}
    void operator()(branchless::Types::name_10) const {}
    void operator()(branchless::Types::name_11) const {}
    void operator()(branchless::Types::name_12) const {}
    void operator()(branchless::Types::name_13) const {}
    void operator()(branchless::Types::name_14) const {}
    void operator()(branchless::Types::name_15) const {}
    void operator()(branchless::Types::name_16) const {}
    void operator()(branchless::Types::name_17) const {}
    void operator()(branchless::Types::name_18) const {}
    void operator()(branchless::Types::name_19) const {}
};
#pragma optimize( "", on )

namespace branch_namespace
{
    enum class BranchEnum
    {
        NAME_1,
        NAME_2,
        NAME_3,
        NAME_4,
        NAME_5,
        NAME_6,
        NAME_7,
        NAME_8,
        NAME_9,
        NAME_10,
        NAME_11,
        NAME_12,
        NAME_13,
        NAME_14,
        NAME_15,
        NAME_16,
        NAME_17,
        NAME_18,
        NAME_19
    };

    constexpr auto toString(BranchEnum en)
    {
        return (en == BranchEnum::NAME_1) ? "NAME_1" :
            (en == BranchEnum::NAME_2) ? "NAME_2" :
            (en == BranchEnum::NAME_3) ? "NAME_3" :
            (en == BranchEnum::NAME_4) ? "NAME_4" :
            (en == BranchEnum::NAME_5) ? "NAME_5" :
            (en == BranchEnum::NAME_6) ? "NAME_6" :
            (en == BranchEnum::NAME_7) ? "NAME_7" :
            (en == BranchEnum::NAME_8) ? "NAME_8" :
            (en == BranchEnum::NAME_9) ? "NAME_9" :
            (en == BranchEnum::NAME_10) ? "NAME_10" :
            (en == BranchEnum::NAME_11) ? "NAME_11" :
            (en == BranchEnum::NAME_12) ? "NAME_12" :
            (en == BranchEnum::NAME_13) ? "NAME_13" :
            (en == BranchEnum::NAME_14) ? "NAME_14" :
            (en == BranchEnum::NAME_15) ? "NAME_15" :
            (en == BranchEnum::NAME_16) ? "NAME_16" :
            (en == BranchEnum::NAME_17) ? "NAME_17" :
            (en == BranchEnum::NAME_18) ? "NAME_18" :
            (en == BranchEnum::NAME_19) ? "NAME_19" : "";
    }

    BranchEnum fromString(const std::string &str)
    {
        if (str == "NAME_1") return BranchEnum::NAME_1;
        if (str == "NAME_2") return BranchEnum::NAME_2;
        if (str == "NAME_3") return BranchEnum::NAME_3;
        if (str == "NAME_4") return BranchEnum::NAME_4;
        if (str == "NAME_5") return BranchEnum::NAME_5;
        if (str == "NAME_6") return BranchEnum::NAME_6;
        if (str == "NAME_7") return BranchEnum::NAME_7;
        if (str == "NAME_8") return BranchEnum::NAME_8;
        if (str == "NAME_9") return BranchEnum::NAME_9;
        if (str == "NAME_10") return BranchEnum::NAME_10;
        if (str == "NAME_11") return BranchEnum::NAME_11;
        if (str == "NAME_12") return BranchEnum::NAME_12;
        if (str == "NAME_13") return BranchEnum::NAME_13;
        if (str == "NAME_14") return BranchEnum::NAME_14;
        if (str == "NAME_15") return BranchEnum::NAME_15;
        if (str == "NAME_16") return BranchEnum::NAME_16;
        if (str == "NAME_17") return BranchEnum::NAME_17;
        if (str == "NAME_18") return BranchEnum::NAME_18;
        if (str == "NAME_19") return BranchEnum::NAME_19;
    }
}


#pragma optimize( "", off )
void branchFunction(branch_namespace::BranchEnum type)
{
    switch (type)
    {
    case branch_namespace::BranchEnum::NAME_1: {} break;
    case branch_namespace::BranchEnum::NAME_2: {} break;
    case branch_namespace::BranchEnum::NAME_3: {} break;
    case branch_namespace::BranchEnum::NAME_4: {} break;
    case branch_namespace::BranchEnum::NAME_5: {} break;
    case branch_namespace::BranchEnum::NAME_6: {} break;
    case branch_namespace::BranchEnum::NAME_7: {} break;
    case branch_namespace::BranchEnum::NAME_8: {} break;
    case branch_namespace::BranchEnum::NAME_9: {} break;
    case branch_namespace::BranchEnum::NAME_10: {} break;
    case branch_namespace::BranchEnum::NAME_11: {} break;
    case branch_namespace::BranchEnum::NAME_12: {} break;
    case branch_namespace::BranchEnum::NAME_13: {} break;
    case branch_namespace::BranchEnum::NAME_14: {} break;
    case branch_namespace::BranchEnum::NAME_15: {} break;
    case branch_namespace::BranchEnum::NAME_16: {} break;
    case branch_namespace::BranchEnum::NAME_17: {} break;
    case branch_namespace::BranchEnum::NAME_18: {} break;
    case branch_namespace::BranchEnum::NAME_19: {} break;
    }
}
#pragma optimize( "", on )



void benchmark(const size_t N)
{
    using Clock = std::chrono::steady_clock;
    BenchmarkResult<Clock> branchless_results;
    BenchmarkResult<Clock> branch;

    branch.create.start = Clock::now();
    std::vector<branch_namespace::BranchEnum> branchVector(N);
    branch.create.finnish = Clock::now();

    branchless_results.create.start = Clock::now();
    std::vector<branchless::Type> branchlessVector(N);
    branchless_results.create.finnish = Clock::now();

    std::vector<std::string> strVector(N);

    std::random_device r;

    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_dist(1, 19);

    branch.fill.start = Clock::now();
    for (size_t i = 0; i < N; ++i)
    {
        switch (uniform_dist(e1))
        {
        case 1: branchVector[i] = branch_namespace::BranchEnum::NAME_1; break;
        case 2: branchVector[i] = branch_namespace::BranchEnum::NAME_1; break;
        case 3: branchVector[i] = branch_namespace::BranchEnum::NAME_1; break;
        case 4: branchVector[i] = branch_namespace::BranchEnum::NAME_1; break;
        case 5: branchVector[i] = branch_namespace::BranchEnum::NAME_1; break;
        case 6: branchVector[i] = branch_namespace::BranchEnum::NAME_1; break;
        case 7: branchVector[i] = branch_namespace::BranchEnum::NAME_1; break;
        case 8: branchVector[i] = branch_namespace::BranchEnum::NAME_1; break;
        case 9: branchVector[i] = branch_namespace::BranchEnum::NAME_1; break;
        case 10: branchVector[i] = branch_namespace::BranchEnum::NAME_10; break;
        case 11: branchVector[i] = branch_namespace::BranchEnum::NAME_11; break;
        case 12: branchVector[i] = branch_namespace::BranchEnum::NAME_12; break;
        case 13: branchVector[i] = branch_namespace::BranchEnum::NAME_13; break;
        case 14: branchVector[i] = branch_namespace::BranchEnum::NAME_14; break;
        case 15: branchVector[i] = branch_namespace::BranchEnum::NAME_15; break;
        case 16: branchVector[i] = branch_namespace::BranchEnum::NAME_16; break;
        case 17: branchVector[i] = branch_namespace::BranchEnum::NAME_17; break;
        case 18: branchVector[i] = branch_namespace::BranchEnum::NAME_18; break;
        case 19: branchVector[i] = branch_namespace::BranchEnum::NAME_19; break;
        }
    }
    branch.fill.finnish = Clock::now();


    branchless_results.fill.start = Clock::now();
    for (size_t i = 0; i < N; ++i)
    {
        switch (uniform_dist(e1))
        {
        case 1: branchlessVector[i] = branchless::Types::name_1{}; break;
        case 2: branchlessVector[i] = branchless::Types::name_2{}; break;
        case 3: branchlessVector[i] = branchless::Types::name_3{}; break;
        case 4: branchlessVector[i] = branchless::Types::name_4{}; break;
        case 5: branchlessVector[i] = branchless::Types::name_5{}; break;
        case 6: branchlessVector[i] = branchless::Types::name_6{}; break;
        case 7: branchlessVector[i] = branchless::Types::name_7{}; break;
        case 8: branchlessVector[i] = branchless::Types::name_8{}; break;
        case 9: branchlessVector[i] = branchless::Types::name_9{}; break;
        case 10: branchlessVector[i] = branchless::Types::name_10{}; break;
        case 11: branchlessVector[i] = branchless::Types::name_11{}; break;
        case 12: branchlessVector[i] = branchless::Types::name_12{}; break;
        case 13: branchlessVector[i] = branchless::Types::name_13{}; break;
        case 14: branchlessVector[i] = branchless::Types::name_14{}; break;
        case 15: branchlessVector[i] = branchless::Types::name_15{}; break;
        case 16: branchlessVector[i] = branchless::Types::name_16{}; break;
        case 17: branchlessVector[i] = branchless::Types::name_17{}; break;
        case 18: branchlessVector[i] = branchless::Types::name_18{}; break;
        case 19: branchlessVector[i] = branchless::Types::name_19{}; break;
        }
    }
    branchless_results.fill.finnish = Clock::now();

    branch.toString.start = Clock::now();
    std::transform(std::begin(branchVector), std::end(branchVector),
                   std::begin(strVector),
                   [](const auto &el)
                   {
                       return branch_namespace::toString(el);
                   });
    branch.toString.finnish = Clock::now();

    branch.fromString.start = Clock::now();
    std::transform(std::begin(strVector), std::end(strVector),
                   std::begin(branchVector),
                   [](const auto &el)
                   {
                       return branch_namespace::fromString(el);
                   });
    branch.fromString.finnish = Clock::now();
    

    branchless_results.toString.start = Clock::now();
    std::transform(std::begin(branchlessVector), std::end(branchlessVector),
                   std::begin(strVector),
                   [](const auto &el)
                   {
                       return branchless::toString(el);
                   });
    branchless_results.toString.finnish = Clock::now();

    branchless_results.fromString.start = Clock::now();
    std::transform(std::begin(strVector), std::end(strVector),
                   std::begin(branchlessVector),
                   [](const auto &el)
                   {
                       return branchless::fromString(el);
                   });
    branchless_results.fromString.finnish = Clock::now();


    branchless_results.function.start = Clock::now();
    BranchlessFunction bf;
    for (const auto &el : branchlessVector)
        boost::apply_visitor(bf, el);
    branchless_results.function.finnish = Clock::now();


    branch.function.start = Clock::now();
    for (const auto &el : branchVector)
        branchFunction(el);
    branch.function.finnish = Clock::now();

    std::cout << "BRANCH\n";
    std::cout << "creation:\t" << BenchmarkResult<Clock>::elapsed(branch.create).count() << "\n";
    std::cout << "fill:\t" << BenchmarkResult<Clock>::elapsed(branch.fill).count() << "\n";
    std::cout << "fromString:\t" << BenchmarkResult<Clock>::elapsed(branch.fromString).count() << "\n";
    std::cout << "toString:\t" << BenchmarkResult<Clock>::elapsed(branch.toString).count() << "\n";
    std::cout << "function:\t" << BenchmarkResult<Clock>::elapsed(branch.function).count() << "\n\n";

    std::cout << "BRANCHLESS\n";
    std::cout << "creation:\t" << BenchmarkResult<Clock>::elapsed(branchless_results.create).count() << "\n";
    std::cout << "fill:\t" << BenchmarkResult<Clock>::elapsed(branchless_results.fill).count() << "\n";
    std::cout << "fromString:\t" << BenchmarkResult<Clock>::elapsed(branchless_results.fromString).count() << "\n";
    std::cout << "toString:\t" << BenchmarkResult<Clock>::elapsed(branchless_results.toString).count() << "\n";
    std::cout << "function:\t" << BenchmarkResult<Clock>::elapsed(branchless_results.function).count() << "\n";
}

int main()
{
    size_t N;
    std::cout << "N: ";
    std::cin >> N;

    benchmark(N);
    return 0;
}