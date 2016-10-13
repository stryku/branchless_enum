#pragma once

#include <cstdlib>
#include <utility>



namespace cexpr
{
    namespace array
    {
        template <typename T, size_t N>
        struct array
        {

            template <size_t i>
            constexpr T const& at()
            {
                return arr[i];
            }

            constexpr T const& operator[](size_t i) const
            {
                return arr[i];
            }
            constexpr T const* begin() const
            {
                return arr;
            }
            constexpr T const* end() const
            {
                return arr + N;
            }

            template <size_t offset, T value>
            constexpr size_t find_next_less() const
            {
                return
                    (offset != N)
                    ? (arr[offset] < value)
                    ? offset
                    : find_next_less<value, offset+1>()
                    : N;
            }

            template <size_t offset, T value>
            constexpr size_t find_next_greater() const
            {
                return
                    (offset!=N)
                    ?   (arr[offset] > value)
                        ?   offset
                        :   find_next_less<value, offset + 1>()
                    : N;
            }

            T arr[N];
        };

        namespace details
        {
            template <typename T, size_t N, size_t ...seq_before, size_t ...seq_after>
            constexpr const array<T, N> set_impl(array<T, N> const& arr,
                                                 size_t index,
                                                 const T& value,
                                                 std::index_sequence<seq_before...>,
                                                 std::index_sequence<seq_after...>)
            {
                return{ { arr[seq_before]..., value, arr[index + seq_after]... } };
            }
        }

        template <size_t index, typename T, size_t N>
        constexpr const array<T, N> set(array<T, N> const& arr, T const& value)
        {
            return details::set_impl(arr, index, value,
                                     std::make_index_sequence <index ? index - 1 : 0>{},
                                     std::make_index_sequence <N - index - 1>{});
        }

        template <size_t i, size_t j, typename T, size_t N>
        constexpr const array<T, N> swap_elements(array<T, N> const& arr)
        {
            return set<i, T, N>(
                set<j, T, N>(arr, arr[j]),
                arr[i]);
        }

        template <size_t i, typename T, size_t N>
        constexpr const T const& at(array<T, N> const& arr)
        {
            return arr[i];
        }
    }
}

class Testable {
public:
    template <bool flag, typename std::enable_if<flag>::type* = nullptr>
    void foo() {  } // (A)

    template <bool flag, typename std::enable_if<!flag>::type* = nullptr>
    void foo() {  } // (B)
};



template <typename T, size_t N>
            struct sort_helper
            {
                T arr[N];
                size_t lo;
                size_t hi;
                size_t q;
            };

template <typename T, size_t N>
struct S
{
  
  template <size_t a, size_t b,
  typename std::enable_if<a < b>::type* = nullptr>
  constexpr static const auto foo(sort_helper<T, N> const& helper)
  {
    return helper.arr;
  }
  
  template <size_t a, size_t b,
  typename std::enable_if<a >= b>::type* = nullptr>
  constexpr static const auto foo(sort_helper<T, N> const&)
  {
    
    
    return foo<a+1, b>( sort_helper<T, N>{foo<a, b+1>( sort_helper<T, N>{cexpr::array::array<T,N>{}, a+1,b,0}),
                                          a,b+1,0}
                       );
  }
};


namespace cexpr
{
    namespace basic
    {
        template <typename T>
        constexpr T inc(T const& value, T const &amount = 1) { return value + amount; }
    }
}

namespace cexpr
{
    namespace algorithm
    {
        namespace details
        {
            template <typename T, size_t N>
            struct sort_helper
            {
                array::array<T, N> arr;
                size_t lo;
                size_t hi;
                size_t q;
            };



            /*template <size_t lo, size_t hi, typename callable>
            struct conditional_call
            {
            template <typename T, size_t N,
            typename = std::enable_if_n<(lo < hi)>>
            constexpr auto operator()(sort_helper<T, N> const& helper) const
            {
            return when_less(helper);
            }

            template <typename T, size_t N,
            typename = std::enable_if_n<(lo >= hi)>>
            constexpr auto operator()(sort_helper<T, N> const& helper) const
            {
            return when_not_less(helper);
            }

            const callable when_less;
            const callable when_not_less;
            };*/

            template <typename T,size_t N, size_t lo, size_t hi, size_t q>
            constexpr const auto make_helper(array::array<T,N> const& arr)
            {
                return sort_helper<T, N>{arr, lo, hi, q};
            }

            template <size_t lo, size_t hi, typename T, size_t N /*sort_helper<typename T, N> const& helper*/ >
            constexpr sort_helper<T, N> partition(array::array<T, N> const& arr/*sort_helper<T, N> const& helper*/) // dzielimy tablice na dwie czesci, w pierwszej wszystkie liczby sa mniejsze badz rowne x, w drugiej wieksze lub rowne od x
            {
                constexpr T x = array::at<lo>(arr);

                constexpr size_t i = arr.find_next_less<lo, x>();
                constexpr size_t j = arr.find_next_greater<hi, x>();

                return
                    i < j
                    ? partition<i + 1, j - 1, T, N>(array::swap_elements<i, j>(arr))
                    : sort_helper<T, N>{ arr, i, j, j };
            }


            template <typename T, size_t N>
            struct conditional
            {
                template <size_t lo, size_t hi, 
                    
  typename std::enable_if<lo >= hi>::type* = nullptr>
                constexpr static const auto sort_impl(sort_helper<T, N> const& helper)
                {
                    return helper.arr;
                }

                template <size_t lo, size_t hi, size_t q,
                    
  typename std::enable_if<lo < hi>::type* = nullptr>
                    constexpr static const auto sort_impl(array::array<T, N> const& arr)
                {
                    /* using type = decltype([](sort_helper<T, N> const& helper) {return helper.arr; });

                    return conditional_call < lo, hi, type) > {
                    [](sort_helper<T, N> const& helper) {return helper.arr; },
                    [](sort_helper<T, N> const& helper)
                    {
                    constexpr const auto new_helper = partition(helper);

                    return sort_impl<new_helper.q + 1, hi>({ sort_impl<lo, new_helper.q>({ new_helper.arr, lo, new_helper.q, 0 }),
                    new_helper.q + 1,
                    hi,
                    0 });
                    }
                    }(helper);*/

                    constexpr const auto new_helper = partition<lo, hi,T,N>(arr);

                    return conditional::sort_impl<new_helper.q + 1, hi, 0>(conditional::sort_impl<lo, new_helper.q, 0>(new_helper.arr));

                    /*return conditional::sort_impl<new_helper.q + 1, hi>({ conditional::sort_impl<lo, new_helper.q>({ new_helper.arr, lo, new_helper.q, 0 }),
                                                                        new_helper.q + 1,
                                                                        hi,
                                                                        0 });*/
                }
            };

            //template <size_t lo, size_t hi, typename T, size_t N/*,
            //    typename = std::enable_if_t<(lo >= hi)>*/>
            //constexpr const array::array<T, N> sort_impl(sort_helper<T, N> const& helper)
            //{
            //    return helper.arr;
            //}

            //template <size_t lo, size_t hi, typename T, size_t N/*,
            //          typename = std::enable_if_t<(lo < hi)>*/>
            //constexpr const array::array<T, N> sort_impl(sort_helper<T, N> const& helper)
            //{
            //    using type = decltype([](sort_helper<T, N> const& helper) {return helper.arr; });

            //    return conditional_call < lo, hi, type) > {
            //        [](sort_helper<T, N> const& helper) {return helper.arr; },
            //        [](sort_helper<T, N> const& helper)
            //        {
            //            constexpr const auto new_helper = partition(helper);

            //            return sort_impl<new_helper.q + 1, hi>({ sort_impl<lo, new_helper.q>({ new_helper.arr, lo, new_helper.q, 0 }),
            //                                            new_helper.q + 1,
            //                                            hi,
            //                                            0 });
            //        }
            //    }(helper);


            //    /*return sort_impl<new_helper.q+1, hi>({ sort_impl<lo, new_helper.q>({new_helper.arr, lo, new_helper.q, 0}),
            //                       new_helper.q+1,
            //                       hi,
            //                       0 });*/
            //}

            
        }

        template <typename T, size_t N, size_t lo = 0, size_t hi = N-1>
        constexpr const array::array<T, N> sort(array::array<T, N> const& arr)
        {
            return details::conditional<T,N>::template sort_impl<lo, hi, 0>(arr);
        }
    }
}

#include <iostream>

constexpr const cexpr::array::array<int, 4> a{ 1,2,22,4 };
constexpr const cexpr::array::array<int, 4> b = cexpr::array::swap_elements<2, 3>(a);
constexpr const cexpr::array::array<int, 4> sorted = cexpr::algorithm::sort(a);

int main()
{
    for (auto el : a)
        std::cout << el << ", ";

    std::cout << "\n";

    for (auto el : b)
        std::cout << el << ", ";

    std::cout << "\n";
    return 0;
}

