#include <bits/stdc++.h>

#define DEBUG

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

template <class It>
void _debug_it(It begin, It end)
{
	std::cerr << "{";
	if (begin != end) {
		_debug(*begin++);
		for (; begin != end; begin++) {
			std::cerr << ", ";
			_debug(*begin);
		}
	}
	std::cerr << "}";
}

template <template <class T> class C, class T>
void _debug(const C<T> &t, const char *d = "")
{
	_debug_it(t.begin(), t.end());
}

template <template <class T, class U> class C, class T, class U>
void _debug(const C<T, U> &t, const char *d = "")
{
	_debug_it(t.begin(), t.end());
}

template <class T, class... U>
void _debug(T t, U... u)
{
	_debug(t);
	std::cerr << ", ";
	_debug(u...);
}

#define dbg(...)                               \
	do {                                       \
		std::cerr << "L" << __LINE__ << ": ["; \
		std::cerr << #__VA_ARGS__ << "] = [";  \
		_debug(__VA_ARGS__, ",");              \
		std::cerr << "]";                      \
		std::cerr << '\n';                     \
	} while (0);
#else // DEBUG
#define dbg(...) ((void)0)
#endif // DEBUG

#ifdef TEST
int main()
{
	dbg(1, 2, "x");
	std::vector<int> x{1, 2, 3};
	std::set<int> y{1, 1, 4, 5, 1, 4};
	std::map<int, int> z{{114, 514}, {1919, 810}};
	dbg(x, y, z);
}
#endif
