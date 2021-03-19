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






namespace test_type_list {

TEST_CASE ( "get last element from a type list with type_list::last", "[type_list]" ) {
    GIVEN ( "A type_list with some types" ) {
        using given = type_list <string, int>;
        
        REQUIRE (is_same_v <given::iter::last, int>);
    }
}

TEST_CASE ( "get first element from a type list with type_list::last", "[type_list]" ) {
    GIVEN ( "A type_list with some types" ) {
        using given = type_list <string, int>;
        
        REQUIRE (is_same_v <given::iter::first, string>);
    }
}

TEST_CASE ("get size of type_list") {
    GIVEN ("A type_list with some types") {
        using given = type_list <string, int>;
        
        REQUIRE (given::size == 2);
    }
}

TEST_CASE ("get type at type_list-index i") {
    
    GIVEN ("A type_list with some types") {
        using TL = type_list <bool, string, int, char const*, string>;
        
        SECTION ("get type_element at index") {
            REQUIRE (is_same_v <TL::type_element_at <0>, bool>);
        }
        
        SECTION ("get type_list at index") {
//            REQUIRE (is_same_v <TL::type_list_at<1>, _type_list <1, string, int, char const*, string>>);
        }
        
    }
}

}


//int main ()
//{
//
//    static_assert(is_same_v <type_list <string, int>::last, int>, "fel");
//
//
//
//
//
//    return 0;
//}



























//TEST_CASE( "Quick check", "[main]" ) {
//
//    REQUIRE( 0 == 0 );
//}


