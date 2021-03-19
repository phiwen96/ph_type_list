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











TEST_CASE ( "get last element from a type list with type_list::last", "[type_list]" ) {
    GIVEN ( "A type_list with some types" ) {
        using given = type_list <string, int>;
        
        REQUIRE (is_same_v <given::last, int>);
    }
}

TEST_CASE ( "get first element from a type list with type_list::last", "[type_list]" ) {
    GIVEN ( "A type_list with some types" ) {
        using given = type_list <string, int>;
        
        REQUIRE (is_same_v <given::first, string>);
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


