#pragma once



template <class... types>
struct type_list;


template <class First, class... Rest>
struct type_list <First, Rest...>
{
    using first = First;
    using last = typename type_list <Rest...>::last;
};


template <class Type>
struct type_list <Type>
{
    using first = Type;
    using last = Type;
};
