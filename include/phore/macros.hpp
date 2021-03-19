#pragma once


namespace {
template <size_t N, size_t M> consteval bool same_strings (char const(&lhs)[N], char const(&rhs)[M]){
    if (N != M)
        return false;
    for (int i = 0; i < N; ++i)
    {
        if (lhs[i] != rhs[i])
            return false;
    }
    return true;
}
#define SAME_TOKEN(x, y) __builtin_choose_expr (same_strings (BOOST_PP_STRINGIZE (x), BOOST_PP_STRINGIZE (y)), 1, 0)
#define macro(x) __builtin_choose_expr (SAME_TOKEN (x, hej), kuk, "jo")

#undef SAME_TOKEN
#undef macro
}
