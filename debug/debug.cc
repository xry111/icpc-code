#include <bits/stdc++.h>

#ifdef DEBUG
template <class T>
void _debug(T t, const char *d = "")
{
	std::cerr << t << d;
}

template <class U, class V>
void _debug(std::pair<U, V> p, const char *d = "")
{
	std::cerr << '(' << p.first << ", " << p.second << ')' << d;
}

// clang-format off
#define _D(C)                                         \
	template <class... T>                             \
	void _debug(const C<T...> &t, const char *d = "") \
	{                                                 \
		std::cerr << '{';                             \
		for (auto x : t)                              \
			_debug(x, ", ");                          \
		std::cerr << '}';                             \
	}
// clang-format on

_D(std::vector)
_D(std::deque)
_D(std::list)
_D(std::set)
_D(std::multiset)
_D(std::unordered_set)
_D(std::unordered_multiset)
_D(std::map)
_D(std::multimap)
_D(std::unordered_map)
_D(std::unordered_multimap)

#undef _D

template <class T, class... U>
void _debug(T t, U... u)
{
	_debug(t);
	std::cerr << ", ";
	_debug(u...);
}

// clang-format off
#define dbg(...)                               \
	do {                                       \
		std::cerr << "L" << __LINE__ << ": ["; \
		std::cerr << #__VA_ARGS__ << "] = [";  \
		_debug(__VA_ARGS__, ",");              \
		std::cerr << "]";                      \
		std::cerr << '\n';                     \
	} while (0);
//clang-format on

#else // DEBUG
#define dbg(...) ((void)0)
#endif // DEBUG

int main()
{
	dbg(1, 2, "x");
	std::vector<int> x{1, 2, 3};
	std::set<int> y{1, 1, 4, 5, 1, 4};
	std::map<int, int> z{{114, 514}, {1919, 810}};
	dbg(x, y, z);
}
