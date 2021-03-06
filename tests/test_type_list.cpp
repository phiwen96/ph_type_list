#include "headers.hpp"




template <auto... values>
struct Math
{
    constexpr auto mean ()
    {
//        conjuntion_t<common_type <
//        return ((), ...)
    }
};



template <int i, class... T>
concept concept_type_list_at = requires () {
    typename type_list_t<T...>::iter::template at<i>::type;
};




namespace test_type_list
{
TEST_CASE ("insert type")
{
    GIVEN ( "A type_list with some types" ) {
        using given = type_list_t <string, int>;
//        REQUIRE (is_same_v <given::iter::next::iter::push<char>::first::type, type_list <char, string, int>>);
    }
}

TEST_CASE ( "get first element", "[type_list]" ) {
    GIVEN ( "A type_list with some types" ) {
        using given = type_list_t <string, int>;
        REQUIRE (is_same_v <given::iter::next::iter::first::type, string>);
    }
}
TEST_CASE ( "get last element", "[type_list]" ) {
    GIVEN ( "A type_list with some types" ) {
        using given = type_list_t <string, int>;
        REQUIRE (is_same_v <given::iter::last::type, int>);
    }
}
TEST_CASE ( "get next element", "[type_list]" ) {
    GIVEN ( "A type_list with some types" ) {
        using given = type_list_t <string, int, char>;
        REQUIRE (is_same_v <given::iter::next::type, int>);
    }
}
TEST_CASE ( "get element before", "[type_list]" ) {
    GIVEN ( "A type_list with some types" ) {
        using given = type_list_t <string, int, char>;
        REQUIRE (is_same_v <given::iter::next::iter::before::type, string>);
    }
}
TEST_CASE ("get size") {
    GIVEN ("A type_list with some types") {
        using given = type_list_t <string, int>;
        REQUIRE (given::size == 2);
    }
}
TEST_CASE ("get type_list at index i") {
    GIVEN ("A type_list with some types") {
        using TL = type_list_t <bool, string, int, char const*, string>;
        SECTION ("get type_element at index") {
            REQUIRE (is_same_v <TL::iter::at<0>::type, bool>);
        }
    }
}
TEST_CASE ("get trailing typelist") {
    GIVEN ("A type_list with some types") {
        using TL = type_list_t <int, string, int, char>;
        REQUIRE (is_same_v<TL::iter::trailing::type, string>);
    }
}
TEST_CASE ("get leading typelist") {
    GIVEN ("A type_list with some types") {
        using TL = type_list_t <int, string, int, char>;
        REQUIRE (is_same_v<TL::iter::next::iter::leading::type, int>);
    }
}
TEST_CASE ("convert typelist to tuple") {
    GIVEN ("A type_list with some types") {
        using TL = type_list_t <int, string, int, char>;
        REQUIRE (is_same_v<TL::iter::next::iter::leading::type, int>);
    }
    GIVEN ("A non-starting typelist index") {
        using TL = type_list_t <int, string, int, char>;
//        REQUIRE (is_same_v <TL::iter::next::tuple, tuple <string, int, char>>);
    }
}
TEST_CASE ("use tuple as template parameters for type_list") {
    GIVEN ("A type_list with some types") {
        using TL = type_list_t <int, string, int, char>;
        REQUIRE (is_base_of_v <TL, type_list_t <tuple <int, string, int, char>>>);
        REQUIRE (is_same_v <type_list_t <tuple <int, string, int, char>>::iter::next::type, string>);
    }
}
TEST_CASE ("use typelist as template parameter for std::tuple") {
    GIVEN ("A type_list with some types") {
        using TL = type_list_t <int, string, int, char>;
        REQUIRE (is_base_of_v <tuple <int, string, int, char>, tuple <TL>>);
    }
}
TEST_CASE ("split typelist into 2 typelists") {
    GIVEN ("A type_list with some types") {
        
        #define TMP_PARAMS_LHS int, string, char
        #define TMP_PARAMS_RHS int, char

        REQUIRE (is_same_v <invoke_result_t <decltype (split_type_list <3, TMP_PARAMS_LHS, TMP_PARAMS_RHS>), type_list_t <TMP_PARAMS_LHS, TMP_PARAMS_RHS>>, type_list_t <TMP_PARAMS_LHS, TMP_PARAMS_RHS>>);
            
        #undef TMP_PARAMS_CALL
        #undef TMP_PARAMS_RESULT
    }
}
TEST_CASE ("pop typelist element") {
    GIVEN ("A type_list with some types") {
        using pop_type = char;
        
        REQUIRE (is_same_v <invoke_result_t <decltype (pop_type_list <0, pop_type, int, char>), type_list_t <pop_type, int, char>>, type_list_t <int, char>>);
        REQUIRE (is_same_v <invoke_result_t <decltype (pop_type_list <1, int, pop_type, char>), type_list_t <int, pop_type, char>>, type_list_t <int, char>>);
        REQUIRE (is_same_v <invoke_result_t <decltype (pop_type_list <2, int, char, pop_type>), type_list_t <int, char, pop_type>>, type_list_t <int, char>>);
        REQUIRE (is_same_v <invoke_result_t <decltype (pop_type_list <0, pop_type>), type_list_t <pop_type>>, type_list_t <>>);
    }
}
//TEMPLATE_PRODUCT_TEST_CASE_METHOD_SIG(Template_Fixture_2, "A", "[", ((typename T, size_t S), T, S),(std::array, Template_Foo_2), ((int,2), (float,6)))

TEST_CASE ("Testing type_list::iter::at")
{
    #define TYPE_LIST_PARAMS \
        int, \
        char, \
        string, \
        char const*
    
    #define TYPE_LIST \
        type_list_t <TYPE_LIST_PARAMS>
    
    SECTION ("Should not work")
    {
        GIVEN (BOOST_PP_STRINGIZE (TYPE_LIST))
        {
            SECTION ("call with -1")
            {
                REQUIRE (concept_type_list_at <-1, TYPE_LIST_PARAMS> == 0);
            }
            SECTION ("call with 3")
            {
                REQUIRE (concept_type_list_at <TYPE_LIST::size, TYPE_LIST_PARAMS> == 0);
            }
        }
    }
    
    SECTION ("Should work")
    {
        GIVEN (BOOST_PP_STRINGIZE (TYPE_LIST))
        {
            SECTION ("call with 0")
            {
                REQUIRE (concept_type_list_at <0, TYPE_LIST_PARAMS> == 1);
            }
            SECTION ("call with elem = size-1")
            {
                REQUIRE (concept_type_list_at <TYPE_LIST::size - 1, TYPE_LIST_PARAMS> == 1);
            }
        }
    }
    
    #undef TYPE_LIST
    #undef TYPE_LIST_PARAMS
    
    
    
}

}

TEST_CASE ("find")
{
//    static_cast <type_list_t <int, double, string>> ()
//    type_list_t <A, B, C>::find <C> ()
    REQUIRE (type_list_t <int, double, string>::find <char> == -1);
    REQUIRE (type_list_t <int, double, string>::find <int> == 0);
    REQUIRE (type_list_t <int, double, string>::find <double> == 1);
    REQUIRE (type_list_t <int, double, string>::find <string> == 2);
}
















int main( int argc, char* argv[] ) {
    
    value_list v (3, "hej");
    
    cout << v.size << endl;
    cout << v.get <0> () << endl;
    cout << push_type_list<1, double>(type_list_t <int, char, string, double> {}) << endl;
    static_assert (is_same_v<decltype (push_type_list<1, double>(type_list_t <int, char, string, double> {})), type_list_t <int, double, char, string, double>>, "");
    
    using type = type_list_t <int, char, string, double>::iter::next::iter::push<double>::iter::first;
    static_assert (is_same_v<type, type_list_t <int, double, char, string, double>>, "");
//    cout << typename type_list<int, char>::iter::template push<char>::first {} << endl;
    
    int result = Catch::Session().run( argc, argv );


    return result;
}










//TEST_CASE( "Quick check", "[main]" ) {
//
//    REQUIRE( 0 == 0 );
//}


