#include "fft_generic.cc"

#if __cplusplus < 201402L
// constexpr is extremely stupid in C++11
// and not available in C++03 at all
#define constexpr const
#endif

constexpr int M = 998244353;
constexpr int pr = 3;

constexpr int pow_mod(int a, int b)
{
	if (!b)
		return 1 % M;
	int t = pow_mod(a, b >> 1);
	t = 1ll * t * t % M;
	if (b & 1)
		t = 1ll * t * a % M;
	return t;
}

constexpr int fft_sz = 262144;
constexpr int o = pow_mod(pr, (M - 1) / fft_sz);
constexpr int log_fft_sz = __builtin_ctz(fft_sz);
constexpr int fft_sz_1 = pow_mod(fft_sz, M - 2);
static_assert(1 << log_fft_sz == fft_sz);
static_assert((M - 1) % fft_sz == 0);

template <class T, size_t S, class M>
constexpr array<T, S> get_power(T o, M m)
{
	array<T, S> ret;
	ret[0] = 1;
	for (size_t i = 1; i < S; i++)
		ret[i] = m(ret[i - 1], o);
	return ret;
}

constexpr int mul_mod(int a, int b)
{
	return 1ll * a * b % M;
}

inline int reduce(int x)
{
	return x + ((x >> 31) & M);
}

inline int add_mod(int x, int y)
{
	return reduce(x + y - M);
}

inline int sub_mod(int x, int y)
{
	return reduce(x - y);
}

/* replace "const" to "constexpr" if fft_sz is small */
const auto opow = get_power<int, fft_sz + 1>(o, mul_mod);

inline void fft(int *a)
{
	_fft<0, 1, fft_sz>(a, &opow[0], mul_mod, add_mod, sub_mod);
}

inline void ifft(int *a)
{
	_fft<fft_sz, -1, fft_sz>(a, &opow[0], mul_mod, add_mod, sub_mod);
	for (int i = 0; i < fft_sz; i++)
		a[i] = mul_mod(a[i], fft_sz_1);
}
