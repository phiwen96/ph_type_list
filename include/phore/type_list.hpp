#pragma once
#include "phore.hpp"



struct null;

template <class Head, class Before, int, class... types>
struct _type_list;

template <class... types>
using type_list = _type_list <null, null, 0, types...>;


template <class...>
struct _type_list_cat;


template <class T, class... U>
struct _type_list <null, null, 0, tuple <T, U...>> : type_list <T, U...> {
    
};

template <class T, class... U>
struct _type_list_cat <T, type_list <U...>> {
    using type = type_list <T, U...>;
};

template <class... A, class... B>
consteval auto cat (type_list <A...>, type_list <B...>) -> decltype (type_list <A..., B...>{})
{
    
}


template <class Head, class Before, int I, class First, class... Rest>
struct _type_list <Head, Before, I, First, Rest...> {
    #define SELF _type_list <Head, Before, I, First, Rest...>
    #define NEXT _type_list <conditional_t <is_same_v <Head, null>, SELF, Head>, SELF, I + 1, Rest...>
    using type          = First;
    using tuple         = tuple <First, Rest...>;
    template <template <class...> class T>
    using change_container = T <First, Rest...>;
    struct iter {
        using before    = Before;
        using next      = NEXT;
        using first     = conditional_t <is_same_v <Head, null>, SELF, Head>;
        using last      = typename NEXT::iter::last;
        using trailing  = next;
        using leading   = Before;
    };
    inline static constexpr int i = I;
    inline static constexpr int size = NEXT::size;
    template <int j>
    using at = conditional_t <j == i, SELF, typename NEXT::template at <j>>;
    #undef NEXT
    #undef SELF
};

template <class Head, class Before, int I, class Type>
struct _type_list <Head, Before, I, Type> {
    #define SELF _type_list <Head, Before, I, Type>
    #define NEXT null
    using type = Type;
    using tuple = tuple <Type>;
    inline static constexpr int i = I;
    inline static constexpr int size = I + 1;
    template <int j>
    using at   = conditional_t <j == i, SELF, null>;
    template <template <class...> class T>
    using change_container = T <Type>;
    struct iter {
        using before        = Before;
        using next          = null;
        using first         = conditional_t <is_same_v <Head, null>, SELF, Head>;
        using last          = SELF;
        using trailing      = null;
        using leading       = Before;
    };
    #undef SELF
    #undef NEXT
};


template <class... T>
struct tuple <type_list <T...>> : std::tuple <T...>
{
    
};





template <class... T, size_t... I1, size_t... I2>
constexpr auto split (type_list <T...> const& t, index_sequence <I1...> ind1, index_sequence <I2...> ind2) -> decltype(auto)
{
    using TL = type_list <T...>;
//    return type_list <int>{};
    return type_list <typename TL::template at<I1>::type...> {};
//      return make_pair (make_tuple (get <I1> (t)...), make_tuple (get <sizeof... (I1) + I2> (t)...));
}

template <size_t splitIndex, class... T, size_t N = sizeof... (T)>
constexpr auto psplit (type_list <T...> const& t) -> decltype (auto)
{
      constexpr size_t i = splitIndex;
      constexpr size_t j = N - splitIndex;
      return split (t, make_index_sequence <i> {}, make_index_sequence <j> {});
}







