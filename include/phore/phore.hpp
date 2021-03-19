#pragma once
using namespace std;
#define MACRO(z, n, text) BOOST_PP_COMMA_IF(n) text
#define SAME_TYPE(x, y) is_same_v <x, y>
#undef MACRO



template <class... T, size_t... I1, size_t... I2>
constexpr auto split (tuple <T...> const& t, index_sequence <I1...> ind1, index_sequence <I2...> ind2) -> decltype(auto)
{
      return make_pair (make_tuple (get <I1> (t)...), make_tuple (get <sizeof... (I1) + I2> (t)...));
}
template <size_t splitIndex, class... T, size_t N = sizeof... (T)>
constexpr auto split (tuple <T...> const& t) -> decltype (auto)
{
      constexpr size_t i = splitIndex;
      constexpr size_t j = N - splitIndex;
      return split (t, make_index_sequence <i> {}, make_index_sequence <j> {});
}
// auto [lhs, rhs] = split<mid> (t);
