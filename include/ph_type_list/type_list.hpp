#pragma once
#include <ph_type/type.hpp>
using namespace std;



struct null;

template <class Head, class Before, int, class... types>
struct _type_list
{
    
};

template <class... types>
using type_list_t = _type_list <null, null, 0, types...>;

template <class... T>
constexpr type_list_t <T...> type_list;


template <class...>
struct _type_list_cat;


template <class T, class... U>
struct _type_list <null, null, 0, tuple <T, U...>> : type_list_t <T, U...> {
    
};




template <class T, class... U>
struct _type_list_cat <T, type_list_t <U...>> {
    using type = type_list_t <T, U...>;
};

template <class... A, class... B>
consteval auto cat (type_list_t <A...>, type_list_t <B...>) -> decltype (type_list_t <A..., B...>{})
{
    
}


template <int curr, int max, int I, class... A>
constexpr auto pop_type_list_impl (type_list_t <A...>, type_list_t <>) -> decltype (auto)
{
    return type_list_t <A...> {};
}




template <int curr, int max, int I, class... A, class B, class... C>
constexpr auto pop_type_list_impl (type_list_t <A...>, type_list_t <B, C...>) -> decltype (auto)
{
    if constexpr (curr == max)
    {
        return type_list_t <A...> {};
        
    } else if constexpr (curr == I)
    {
        return pop_type_list_impl <curr + 1, max, I> (type_list_t <A...> {}, type_list_t <C...> {});
        
    } else
    {
        return pop_type_list_impl <curr + 1, max, I> (type_list_t <A..., B> {}, type_list_t <C...> {});
    }
}


template <int i, class... T>
requires (i >= 0 and i < sizeof... (T))
constexpr auto pop_type_list (type_list_t <T...>) -> decltype (auto)
{

    return pop_type_list_impl <0, sizeof... (T), i> (type_list_t <> {}, type_list_t <T...> {});

}




template <int curr, int max, int i, class A, class... B, class C, class... D>
constexpr auto push_type_list_impl (type_list_t <B...> read, type_list_t <C, D...> reading) -> decltype (auto)
{
//    if constexpr (curr == max)
//    {
//        return type_list <A...> {};
//
//    }
    if constexpr (curr == i)
    {
        return type_list_t <B..., A, C, D...> {};//push_type_list_impl <curr + 1, max, I, A> (type_list <A, B, C...> {});
        
    }
    else
    {
        return push_type_list_impl <curr + 1, max, i, A> (type_list_t <B..., C> {}, type_list_t <D...> {});
    }
}

template <int i, class T, class... U>
requires (i >= 0 and i < sizeof... (U))
constexpr auto push_type_list (type_list_t <U...>) -> decltype (auto)
{

    return push_type_list_impl <0, sizeof... (U), i, T> (type_list_t <> {}, type_list_t <U...> {});

}


template <class Head, class Before, int I, class First, class... Rest>
struct _type_list <Head, Before, I, First, Rest...> {
    #define SELF _type_list <Head, Before, I, First, Rest...>
    #define NEXT _type_list <conditional_t <is_same_v <Head, null>, SELF, Head>, SELF, I + 1, Rest...>
    using value_type          = First;
    using as_tuple         = tuple <First, Rest...>;
    template <template <class...> class T>
    using change_container = T <First, Rest...>;
    inline static constexpr int size = NEXT::size;
    struct iter {
        inline static constexpr int i = I;
        using before    = Before;
        using next      = NEXT;
        using first     = conditional_t <is_same_v <Head, null>, SELF, Head>;
        using last      = typename NEXT::iter::last;
        using trailing  = next;
        using leading   = Before;
        using pop       = decltype (pop_type_list <i> (first {}));
        template <class X>
        using push       = decltype (push_type_list <i, X> (first {}));
        template <int j>
        requires (j >= 0 and j < size)
        using at = conditional_t <j == i, SELF, typename NEXT::iter::template at <j>>;
    };
    template <int j>
//    requires (j >= 0 and j < size)
    using type_at = conditional_t <j == I, value_type, typename NEXT::template type_at <j>>;
    template <typename X>
    inline static constexpr bool _has ()
    {
        if constexpr (is_same_v <X, value_type>)
            return true;
        return  NEXT::template _has <X> ();
    }
    template <typename X>
    inline static constexpr bool has = _has <X> ();
    
    template <typename... X>
    inline static constexpr bool has_variant (variant <X...> const& v)
    {
        if (visit ([]<typename Y>(Y const&)constexpr -> bool{return is_same_v <Y, value_type>;}, v))
            return true;
//        if constexpr (is_same_v <X, type>)
//            return true;
        else
            return  NEXT::template has_variant <X...> (v);
    }
    
    template <typename... X>
    inline static constexpr bool has_any (any const& a)
    {
        if (a.type () == typeid (value_type))
            return true;
//        if constexpr (is_same_v <X, type>)
//            return true;
        else
            return  NEXT::template has_any <X...> (a);
    }
    
    template <template <typename...> typename Y, typename... X>
    inline static constexpr bool has_vari ( Y <X...> const& a)
    {
        if (type <value_type> == a)
            return true;
//        if constexpr (is_same_v <X, type>)
//            return true;
        else
            return  NEXT::template has_vari (a);
    }
    
  
    
    template <typename P>
    inline static constexpr auto _find () -> int
    {
        if constexpr (is_same_v <P, value_type>)
        {
//            cout << "sho" << endl;
            return I;
        }
            
        else
            return NEXT::template _find <P> ();
    }
    
    template <typename P>
    inline static constexpr int find = _find <P> ();
    
    #undef NEXT
    #undef SELF
};

template <class Head, class Before, int I, class Type>
struct _type_list <Head, Before, I, Type> {
    #define SELF _type_list <Head, Before, I, Type>
    #define NEXT null
    using value_type = Type;
    using as_tuple = tuple <Type>;
    inline static constexpr int i = I;
    inline static constexpr int size = I + 1;
    template <template <class...> class T>
    using change_container = T <Type>;
    struct iter {
        using before        = Before;
        using next          = null;
        using first         = conditional_t <is_same_v <Head, null>, SELF, Head>;
        using last          = SELF;
        using trailing      = null;
        using leading       = Before;
        template <int j>
        requires (j >= 0 and j < size)
        using at   = conditional_t <j == i, SELF, null>;
        template <class X>
        using push       = decltype (push_type_list <i, X> (first {}));
    };
    template <int j>
    using type_at = conditional_t <j == I, value_type, null>;
    template <typename X>
    inline static constexpr bool _has ()
    {
        if constexpr (is_same_v <X, value_type>)
            return true;
        return false;
    }
    template <typename... X>
    inline static constexpr bool has_variant (variant <X...> const& v)
    {
        if (visit ([]<typename Y>(Y const&){return is_same_v <Y, value_type>;}, v))
            return true;
//        if constexpr (is_same_v <X, type>)
//            return true;
        return  false;
    }
    template <typename... X>
    inline static constexpr bool has_any (any const& a)
    {
        if (a.type () == typeid (value_type))
            return true;
//        if constexpr (is_same_v <X, type>)
//            return true;
        else
            return false;
    }
    
    template <template <typename...> typename Y, typename... X>
    inline static constexpr bool has_vari (Y <X...> const& a)
    {
        if (type <value_type> == a)
            return true;
//        if constexpr (is_same_v <X, type>)
//            return true;
        else
            return false;
    }
    
    template <typename P>
    inline static constexpr auto _find () -> int
    {
        if constexpr (is_same_v <P, value_type>)
            return I;
        else
            return -1;
    }
    
    
    
    #undef SELF
    #undef NEXT
};







template <class... T>
struct tuple <type_list_t <T...>> : std::tuple <T...>
{
    
};






template <size_t splitIndex, class... T, size_t N = sizeof... (T)>
constexpr auto split_type_list (type_list_t <T...> const& t) -> decltype (auto)
{
      constexpr size_t i = splitIndex;
      constexpr size_t j = N - splitIndex;
    
      return [] <size_t... I1, size_t... I2> (type_list_t <T...> const& t,
                                              index_sequence <I1...> ind1,
                                              index_sequence <I2...> ind2) -> decltype (auto)
        {
            using TL = type_list_t <T...>;
            return type_list_t <typename TL::iter::template at <I1>::type..., typename TL::iter::template at <sizeof... (I1) + I2>::type...> {};
        }
    
        (t, make_index_sequence <i> {}, make_index_sequence <j> {});
}




template <size_t insertIndex, class... T, size_t N = sizeof... (T)>
constexpr auto insert_type_list (type_list_t <T...> const& t) -> decltype (auto)
{
      constexpr size_t i = insertIndex;
      constexpr size_t j = N - insertIndex;
    
      return [] <size_t... I1, size_t... I2> (type_list_t <T...> const& t,
                                              index_sequence <I1...> ind1,
                                              index_sequence <I2...> ind2) -> decltype (auto)
        {
            using TL = type_list_t <T...>;
            return type_list_t <typename TL::iter::template at <I1>::type..., typename TL::iter::template at <sizeof... (I1) + I2>::type...> {};
        }
    
        (t, make_index_sequence <i> {}, make_index_sequence <j> {});
}




















template <class T, class U, class... V>
void print_type_list (ostream& os, type_list_t <T, U, V...>)
{
    os << typeid (T).name () << ", ";
    print_type_list (os, type_list_t <U, V...> {});
}

template <class T>
void print_type_list (ostream& os, type_list_t <T>)
{
    os << typeid (T).name ();
    os << ">";
}



template <class T, class... U>
ostream& operator<< (ostream& os, type_list_t <T, U...> const& s) {
    os << "type_list <";
    print_type_list (os, s);
    return os;
}






//template <std::size_t... Ns>
//struct index_sequence {};
//
//template <std::size_t N, std::size_t... Is>
//auto make_index_sequence_impl() {
//    // only one branch is considered. The other may be ill-formed
//    if constexpr (N == 0) return index_sequence<Is...>(); // end case
//    else return make_index_sequence_impl<N-1, N-1, Is...>(); // recursion
//}
//
//template <std::size_t N>
//using make_index_sequence = std::decay_t<decltype(make_index_sequence_impl<N>())>;






/**
 ///////////////////////////////////////////////////
 ///  TYPE_AT
 //////////////////////////////////////////////////
 */





template <int I, typename T, typename... U>
struct type_at_t : type_at_t <I + 1, U...>
{
//    using type_at_t <I + 1, U...>::at;
    using type = T;
    
    template <int i>
    requires (i >= I and i < sizeof... (U) + 1)
    using at = conditional_t <i == I, type_at_t, typename type_at_t <I, U...>::template at <I>>;
    


};

template <typename T, typename U, typename... V>
struct next_type_t
{
    using type = U;
};

template <typename T, typename... U>
struct tail_type_t
{
    using type = tail_type_t <U...>;
};



template <typename... T>
using next_type = typename next_type_t <T...>::type;

template <int I, typename T>
struct type_at_t <I, T>
{
    using type = T;
    
    template <int i>
    requires (i == I)
    using at = type_at_t <I, T>;
};


template <int i, typename... T>
using type_at = typename type_at_t <0, T...>::template at <i>::type;

static_assert (is_same_v <type_at <0, int, double, string>, int>, "");



//template <

template <int i, typename... T>
auto test_at_imp ()
{
    auto fun = []<int j, int me, typename A, typename... B>(auto f){
        return (j == me ? 0 : 2);
        if constexpr (j == me)
        {
            return declval <A> ();
        } else
        {
            return f.template operator() <j, me + 1, B...> ();
        }
    };
    return fun.template operator () <i, 0, T...> (fun);
}



template <int i, typename... T>
auto test_at_imp_2 ()
{
    auto a = [] <size_t... I> (index_sequence <I...>) {
//        (([]<int j>{if (j == 2) return}), ...);
//        return ()
    } (make_index_sequence <sizeof... (T)> ());
}

//template <int i, int I, typename T, typename... U>
//using test_at_imp = conditional_t <i == I, T, test_at_imp <i, I + 1, U...>>;

template <int i, typename... T>
requires (i >= 0 and i <  sizeof... (T))
using test_at = decltype (test_at_imp <i, T...>());
