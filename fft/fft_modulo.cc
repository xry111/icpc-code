#include <bits/stdc++.h>
using namespace std;

const int M = 998244353;
const int o = 996173970; // o**262144 = 1
const int fft_sz = 262144;
const int log_fft_sz = __builtin_ctz(fft_sz);
const int fft_sz_1 = 998240545;

// need to be initialized, see below
int opow[fft_sz + 1];

inline int reduce(int x)
{
	return x + ((x >> 31) & M);
}

template <int X, int Y>
void _fft(int *a)
{
	change(a, fft_sz);
	for (int step = 2; step <= fft_sz; step += step) {
		int len = step >> 1;
		int log_om1 = fft_sz / step;
		for (int k = 0; k < fft_sz; k += step) {
			int upp = k + len;
			int log_om = X;
			for (int j = k; j < upp; j++) {
				long long om = opow[log_om];
				int t = om * a[j + len] % M;
				int u = a[j];
				a[j] = reduce(u + t - M);
				a[j + len] = reduce(u - t);
				log_om += Y * log_om1;
			}
		}
	}
}

inline void fft(int *a)
{
	_fft<0, 1>(a);
}

inline void ifft(int *a)
{
	_fft<fft_sz, -1>(a);
	for (int i = 0; i < fft_sz; i++)
		a[i] = 1ll * a[i] * fft_sz_1 % M;
}

int main()
{
	opow[0] = 1;
	for (int i = 1; i <= fft_sz; i++)
		opow[i] = opow[i - 1] * 1ll * o % M;
}
