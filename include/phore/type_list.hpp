#pragma once



template <class... types>
struct type_list;


template <class first, class... rest>
struct type_list <first, rest...>
{
    using last = typename type_list <rest...>::last;
};


template <class type>
struct type_list <type>
{
    using last = type;
};
