#pragma once



template <int, class... types>
struct _type_list;




template <int I, class First, class... Rest>
struct _type_list <I, First, Rest...>
{
#define SELF _type_list <I, First, Rest...>
#define NEXT _type_list <I + 1, Rest...>

    
    using first = First;
    using last = typename NEXT::last;
    inline static constexpr int i = I;
    inline static constexpr int size = NEXT::size;
    
    template <int j>
    using at = conditional_t <j == I, SELF, NEXT>;
    
    template <int L>
    struct from
    {
        template <int K>
        struct to
        {
//            using type =
        };
    };
    
    
    
#undef NEXT
#undef SELF
};


template <int I, class Type>
struct _type_list <I, Type>
{
    using first = Type;
    using last = Type;
    inline static constexpr int i = I;
    inline static constexpr int size = I + 1;
};


template <class... types>
using type_list = _type_list <0, types...>;








