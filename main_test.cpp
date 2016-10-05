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

//
//struct Branchless
//{
//    struct Types
//    {
//        constexpr static int start = 11;
//        struct t1
//        {
//            constexpr static int value = start + 0;
//            constexpr static auto toString() { return "t1"; }
//        };
//        struct t2
//        {
//            constexpr static int value = start + 1;
//            constexpr static auto toString() { return "t2"; }
//        };
//    };
//
//    static Types::t1 t1;
//    static Types::t2 t2;
//
//    using Type = boost::variant<Types::t1, Types::t2>;
//
//    template <typename T>
//    constexpr static bool is_this_type_v = is_any_of_v<T, Types::t1, Types::t2>;
//
//    struct detail
//    {
//        struct value_visitor : public boost::static_visitor<int>
//        {
//        public:
//            constexpr int operator()(Branchless::Types::t1) const
//            {
//                return Branchless::Types::t1::value;
//            }
//            constexpr int operator()(Branchless::Types::t2) const
//            {
//                return Branchless::Types::t2::value;
//            }
//        };
//
//        template <typename T>
//        static constexpr int value(T)
//        {
//            return T::value;
//        }
//
//        static int value(const Type &t)
//        {
//            return boost::apply_visitor(value_visitor{}, t);
//        }
//    };
//
//    template <typename T>
//    static constexpr auto toString(T)
//    {
//        return T::toString();
//    }
//
//    static auto toString(const Type &t)
//    {
//        return boost::apply_visitor([](const auto &val) { return val.toString(); },
//                                    t);
//    }
//
//    static Type fromString(const std::string &str)
//    {
//        if (str == Types::t1::toString())  return Types::t1{};
//        if (str == Types::t2::toString())  return Types::t2{};
//
//        return{};
//    }
//};
//
//template <typename T, typename T2,
//          typename = std::enable_if<Branchless::is_this_type_v<T> || 
//                                    Branchless::is_this_type_v<T2>
//                                    
//    >>
//constexpr bool operator==(const T&, const T2&)
//{
//    return false;
//}
//
//template <typename T,
//          typename = std::enable_if_t<Branchless::is_this_type_v<T>>>
//constexpr bool operator==(const T&, const T&)
//{
//    return true;
//}

branchless_enum(branchless, name_1, name_2);

struct BranchlessVisitor : public boost::static_visitor<>
{
public:
    void operator()(branchless::Types::name_1) const
    {
        std::cout << "hello t1\n";
    }
    void operator()(branchless::Types::name_2) const
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
    auto branchless = branchless::fromString(argv[1]);
    auto branchless2 = branchless::fromString(argv[2]);

    auto constexp = branchless::name_1;
    auto constexp2 = branchless::name_2;

    std::cout << "magic\n";
    foo(magic);

    std::cout << "\n\nbranchless\n";
    boost::apply_visitor(BranchlessVisitor{}, branchless);

    std::cout << "\n\nconstexpr compare\n";
    if (constexp == constexp2)
        std::cout << branchless::toString(constexp) << " == " << branchless::toString(constexp2);
    else
        std::cout << branchless::toString(constexp) << " != " << branchless::toString(constexp2);

    std::cout << "\n";
    if (constexp == constexp)
        std::cout << branchless::toString(constexp) << " == " << branchless::toString(constexp);
    else
        std::cout << branchless::toString(constexp) << " != " << branchless::toString(constexp);

    std::cout << "\n\nbranchless compare\n";
    if (branchless == branchless2)
        std::cout << branchless::toString(branchless) << " == " << branchless::toString(branchless2);
    else
        std::cout << branchless::toString(branchless) << " != " << branchless::toString(branchless2);

    std::cout << "\n\n";
    return 0;
}
//
//#include <boost/preprocessor/variadic/size.hpp>
//
//#pragma once
//
//#define PP_NARG(...) \
//    
////PP_NARG_(__VA_ARGS__,PP_RSEQ_N())
//#define PP_NARG_(...) \
//         PP_ARG_N(__VA_ARGS__)
//#define PP_ARG_N( \
//          _1, _2, _3, _4, _5, _6, _7, _8, _9,_10, \
//         _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
//         _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
//         _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
//         _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
//         _51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
//         _61,_62,_63,N,...) N
//#define PP_RSEQ_N() \
//         63,62,61,60,                   \
//         59,58,57,56,55,54,53,52,51,50, \
//         49,48,47,46,45,44,43,42,41,40, \
//         39,38,37,36,35,34,33,32,31,30, \
//         29,28,27,26,25,24,23,22,21,20, \
//         19,18,17,16,15,14,13,12,11,10, \
//         9,8,7,6,5,4,3,2,1,0
//
//# define EMPTY(...)
//# define DEFER(...) __VA_ARGS__ EMPTY()
//# define OBSTRUCT(...) __VA_ARGS__ DEFER(EMPTY)()
//# define EXPAND(...) __VA_ARGS__
//
//#define EVAL(...)  EVAL1(EVAL1(EVAL1(__VA_ARGS__)))
//#define EVAL1(...) EVAL2(EVAL2(EVAL2(__VA_ARGS__)))
//#define EVAL2(...) EVAL3(EVAL3(EVAL3(__VA_ARGS__)))
//#define EVAL3(...) EVAL4(EVAL4(EVAL4(__VA_ARGS__)))
//#define EVAL4(...) EVAL5(EVAL5(EVAL5(__VA_ARGS__)))
//#define EVAL5(...) __VA_ARGS__
//
//#define CAT(a, ...) PRIMITIVE_CAT(a, __VA_ARGS__)
//#define PRIMITIVE_CAT(a, ...) a ## __VA_ARGS__
//
////#define INC(x) PRIMITIVE_CAT(INC_, x)
////#define INC_0 1
////#define INC_1 2
////#define INC_2 3
////#define INC_3 4
////#define INC_4 5
////#define INC_5 6
////#define INC_6 7
////#define INC_7 8
////#define INC_8 9
////#define INC_9 9
////
////#define DEC(x) PRIMITIVE_CAT(DEC_, x)
////#define DEC_0 0
////#define DEC_1 0
////#define DEC_2 1
////#define DEC_3 2
////#define DEC_4 3
////#define DEC_5 4
////#define DEC_6 5
////#define DEC_7 6
////#define DEC_8 7
////#define DEC_9 8
//
//#define CHECK_N(x, n, ...) n
//#define CHECK(...) CHECK_N(__VA_ARGS__, 0,)
//
//#define NOT(x) CHECK(PRIMITIVE_CAT(NOT_, x))
//#define NOT_0 ~, 1,
//
//#define COMPL(b) PRIMITIVE_CAT(COMPL_, b)
//#define COMPL_0 1
//#define COMPL_1 0
//
//#define BOOL(x) COMPL(NOT(x))
//
//#define IIF(c) PRIMITIVE_CAT(IIF_, c)
//#define IIF_0(t, ...) __VA_ARGS__
//#define IIF_1(t, ...) t
//
//#define IF(c) IIF(BOOL(c))
//
//#define EAT(...)
//#define EXPAND(...) __VA_ARGS__
//#define WHEN(c) IF(c)(EXPAND, EAT)
//
////#define REPEAT(count, macro, ...) \
////    WHEN(count) \
////    ( \
////        OBSTRUCT(REPEAT_INDIRECT) () \
////        ( \
////            DEC(count), macro, __VA_ARGS__ \
////        ) \
////        OBSTRUCT(macro) \
////        ( \
////            DEC(count), __VA_ARGS__ \
////        ) \
////    )
////#define REPEAT_INDIRECT() REPEAT
//
//////An example of using this macro
////#define M(i, _) i
//////EVAL(REPEAT(9, M, ~)) // 0 1 2 3 4 5 6 7
//
//#define cos_0(...) 55, __VA_ARGS__
//#define cos_1(...) 56, __VA_ARGS__
//#define cos_2(...) 57, __VA_ARGS__
//#define cos(count, ...) EVAL(PRIMITIVE_CAT(cos_, count)(__VA_ARGS__))
//
//#define branchless_enum(name, ...)  cos(EVAL(PP_NARG(__VA_ARGS__)), __VA_ARGS__)
//
//
////EVAL(PP_NARG(a,b))
//branchless_enum(nazwa, a, w)