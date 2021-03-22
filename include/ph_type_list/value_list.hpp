#pragma once
#include "type_list.hpp"
using namespace std;

namespace {
#define __ACA(number, middle, elem) if constexpr (_I==number-1) return (decltype (elem) const&) elem;

#define PH_STRUCTURED_BINDING(...)                                                                                      \
template <size_t _I> auto get() const -> decltype (auto)                                                                                      \
{                                                                                                                                                                            \
BOOST_PP_SEQ_FOR_EACH (__ACA, +, BOOST_PP_VARIADIC_TO_SEQ (__VA_ARGS__))                                                                                       \
}                                                                                                                                                                            \
};                                                                                                                                                                            \
namespace std {                                                                                                                                                                            \
\
template<>                                                                                                                                                                             \
struct tuple_size<SELF> : integral_constant <size_t, BOOST_PP_VARIADIC_SIZE (__VA_ARGS__)>                                                                                       \
{                                                                                                                                                                            \
\
};                                                                                                                                                                            \
\
template<size_t _I>                                                                                                                                                                             \
struct std::tuple_element <_I, SELF>                                                                                                                                                                             \
{                                                                                                                                                                             \
using type = decltype (declval<SELF>().get<_I>());                                                                                                                                                                             \
};
}



template <int, class...>
struct _value_list;


template <int I, class T, class... U>
struct _value_list <I, T, U...> : _value_list <I + 1, U...>
{
    #define SELF _value_list <I, T, U...>
    #define PARENT _value_list <I + 1, U...>
 
    using PARENT::get;
    
    T t;
    
    
    
    constexpr _value_list (T const& t, U const&... u) : t (t), PARENT (u...)
    {
        
    }
    
    template <int i>
    constexpr auto get () -> decltype (auto)
    requires (i == I)
    {
        return t;
    }
    
    constexpr auto operator[] (int i) const -> T const&
    requires (i != I)
    {
        if constexpr (i != I)
            return PARENT::operator[] (i);
        return t;
    }
//    PH_STRUCTURED_BINDING (t)
};

template <int I, class T>
struct _value_list <I, T>
{
    T t;
    
    constexpr _value_list (T const& t) : t (t)
    {
        
    }
    
    template <int i>
    constexpr auto get () -> decltype (auto)
    requires (i == I)
    {
        return t;
    }
    
    constexpr auto operator[] (int i) -> decltype (auto)
    {
        return t;
    }
    
    
    
};



template <class... T>
struct value_list : _value_list <0, T...>
{
#define PARENT _value_list <0, T...>

    using PARENT::_value_list;
    using PARENT::operator[];
    using PARENT::get;
    
    inline static constexpr int size = sizeof... (T);
};

template <class... T>
value_list (T...) -> value_list <T...>;


//template <class... T>
//auto __value_list (T&&... t) -> decltype (auto)
//{
//    return _value_list <T...> (forward <T> (t)...);
//}


//template <class... T>
//using value_list =  decltype (__value_list (declval <T> ()...));
