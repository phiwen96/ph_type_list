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


TEST_CASE () {
    
}





namespace test_type_list
{
TEST_CASE ( "get first element", "[type_list]" ) {
    GIVEN ( "A type_list with some types" ) {
        using given = type_list <string, int>;
        REQUIRE (is_same_v <given::iter::first, string>);
    }
}
TEST_CASE ( "get last element", "[type_list]" ) {
    GIVEN ( "A type_list with some types" ) {
        using given = type_list <string, int>;
        REQUIRE (is_same_v <given::iter::last::type, int>);
    }
}
TEST_CASE ( "get next element", "[type_list]" ) {
    GIVEN ( "A type_list with some types" ) {
        using given = type_list <string, int, char>;
        REQUIRE (is_same_v <given::iter::next::type, int>);
    }
}
TEST_CASE ( "get element before", "[type_list]" ) {
    GIVEN ( "A type_list with some types" ) {
        using given = type_list <string, int, char>;
        REQUIRE (is_same_v <given::iter::next::iter::before::type, string>);
    }
}
TEST_CASE ("get size") {
    GIVEN ("A type_list with some types") {
        using given = type_list <string, int>;
        REQUIRE (given::size == 2);
    }
}
TEST_CASE ("get type_list at index i") {
    GIVEN ("A type_list with some types") {
        using TL = type_list <bool, string, int, char const*, string>;
        SECTION ("get type_element at index") {
            REQUIRE (is_same_v <TL::at<0>::type, bool>);
        }
    }
}
TEST_CASE ("get trailing typelist") {
    GIVEN ("A type_list with some types") {
        using TL = type_list <int, string, int, char>;
        REQUIRE (SAME_TYPE (TL::iter::trailing::type, string));
    }
}
TEST_CASE ("get leading typelist") {
    GIVEN ("A type_list with some types") {
        using TL = type_list <int, string, int, char>;
        REQUIRE (SAME_TYPE (TL::iter::next::iter::leading::type, int));
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


