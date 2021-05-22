#include <bits/stdc++.h>
using namespace std;

// If necessary, change it to custom complex type.
// std::complex is slow on some platform.
typedef complex<double> C;

const double pi = acos(-1);
const int fft_sz = 262144;
const C o = {cos(2 * pi / fft_sz), sin(2 * pi / fft_sz)}; // o**262144 = 1
const int log_fft_sz = __builtin_ctz(fft_sz);
const double fft_sz_1 = 1.0 / fft_sz;

// need to be initialized, see below
C opow[fft_sz + 1];

template <int X, int Y>
void _fft(C *a)
{
	change(a, fft_sz);
	for (int step = 2; step <= fft_sz; step += step) {
		int len = step >> 1;
		int log_om1 = fft_sz / step;
		for (int k = 0; k < fft_sz; k += step) {
			int upp = k + len;
			int log_om = X;
			for (int j = k; j < upp; j++) {
				C om = opow[log_om];
				C t = om * a[j + len];
				C u = a[j];
				a[j] = u + t;
				a[j + len] = u - t;
				log_om += Y * log_om1;
			}
		}
	}
}

inline void fft(C *a)
{
	_fft<0, 1>(a);
}

inline void ifft(C *a)
{
	_fft<fft_sz, -1>(a);
	for (int i = 0; i < fft_sz; i++)
		a[i] = a[i] * fft_sz_1;
}

int main()
{
	opow[0] = 1;
	for (int i = 1; i <= fft_sz; i++)
		opow[i] = opow[i - 1] * o;
}
