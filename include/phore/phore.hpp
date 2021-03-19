#pragma once
using namespace std;
#define MACRO(z, n, text) BOOST_PP_COMMA_IF(n) text
#define SAME_TYPE(x, y) is_same_v <x, y>
#undef MACRO



 // expands to class, class, class
