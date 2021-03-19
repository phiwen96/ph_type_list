#pragma once


struct null;


template <class Before, int, class... types>
struct _type_list;




template <class Before, int I, class First, class... Rest>
struct _type_list <Before, I, First, Rest...>
{
#define SELF _type_list <Before, I, First, Rest...>
#define NEXT _type_list <SELF, I + 1, Rest...>
    
    using before = Before;
    using next = NEXT;
    using type = First;
    using first = First;
    using last = typename NEXT::last;
    inline static constexpr int i = I;
    inline static constexpr int size = NEXT::size;
    
    template <int j>
    using type_element_at = conditional_t <j == i, First, typename NEXT::template type_element_at <j>>;

    
    template <int L>
    struct from
    {
        template <int K>
        struct to
        {
//            using type =
        };
    };
    
    
//#undef AT_ARGS_0
//#undef AT_ARGS_1
//#undef NEXT
//#undef SELF
};


template <class Before, int I, class Type>
struct _type_list <Before, I, Type>
{
    using before = Before;
    using type = Type;
    using first = Type;
    using last = Type;
    using next = null;
    inline static constexpr int i = I;
    inline static constexpr int size = I + 1;
    
    template <int j>
    using type_element_at = conditional_t <j == i, type, null>;
};


template <class... types>
using type_list = _type_list <null, 0, types...>;








