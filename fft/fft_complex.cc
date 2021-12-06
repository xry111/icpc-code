#include "fft_generic.cc"

#if __cplusplus < 201402L
// constexpr is extremely stupid in C++11
// and not available in C++03 at all
#define constexpr const
#endif

// If necessary, change it to custom complex type.
// std::complex is slow on some platform.
typedef complex<double> C;

constexpr double pi = acos(-1);
constexpr int fft_sz = 262144;
constexpr C o = {cos(2 * pi / fft_sz), sin(2 * pi / fft_sz)};
constexpr int log_fft_sz = __builtin_ctz(fft_sz);
constexpr double fft_sz_1 = 1.0 / fft_sz;
static_assert(1 << log_fft_sz == fft_sz);

template <class T, size_t S, class M>
constexpr array<T, S> get_power(T o, M m)
{
	array<T, S> ret;
	ret[0] = 1;
	for (size_t i = 1; i < S; i++)
		ret[i] = m(ret[i - 1], o);
	return ret;
}

/* replace "const" to "constexpr" if fft_sz is small */
const auto opow = get_power<C, fft_sz + 1>(o, multiplies<C>());

inline void fft(C *a)
{
	_fft<0, 1, fft_sz>(a, &opow[0], multiplies<C>(), plus<C>(), minus<C>());
}

inline void ifft(C *a)
{
	_fft<fft_sz, -1, fft_sz>(a, &opow[0], multiplies<C>(), plus<C>(),
	                         minus<C>());
	for (int i = 0; i < fft_sz; i++)
		a[i] = a[i] * fft_sz_1;
}
