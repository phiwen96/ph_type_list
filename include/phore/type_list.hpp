#pragma once


struct null;


template <int, class... types>
struct _type_list;




template <int I, class First, class... Rest>
struct _type_list <I, First, Rest...>
{
#define SELF _type_list <I, First, Rest...>
#define NEXT _type_list <I + 1, Rest...>

    using next = typename NEXT::type;
    using type = First;
    using first = First;
    using last = typename NEXT::last;
    inline static constexpr int i = I;
    inline static constexpr int size = NEXT::size;
    
#define at \
    X (type_list_at) Y (SELF, NEXT)\
    X (type_at)      Y (First, (tuple_element_t <I + 1, tuple <Rest...>>))
    
#define Y(a, b) conditional_t <j == I, a, b>;
    
#define X(y) \
    template <int j> \
    requires (j >= 0 and j < size) \
    using y = at
    
#undef X
#undef Y
#undef at
    
    
    
    
    
#define x
    template <int j>
    requires (j >= 0 and j < size)
    using type_list_at = conditional_t <j == I, SELF, NEXT>;
    
    
    
   
    
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
    
    using type = Type;
    using first = Type;
    using last = Type;
    using next = null;
    inline static constexpr int i = I;
    inline static constexpr int size = I + 1;
};


template <class... types>
using type_list = _type_list <0, types...>;








