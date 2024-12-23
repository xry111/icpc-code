#include <bits/stdc++.h>
using namespace std;

template <class T>
void change(T *a, int n)
{
	int i, j, k;
	for (i = 1, j = n >> 1; i < n - 1; i++) {
		if (i < j)
			swap(a[i], a[j]);
		k = n >> 1;
		while (j >= k) {
			j -= k;
			k /= 2;
		}
		j += k;
	}
}

template <int X, int Y, int SZ, class T, class M, class A, class S>
void _fft(T *a, const T *opow, M mul, A add, S sub)
{
	change(a, SZ);
	for (int step = 2; step <= SZ; step += step) {
		int len = step >> 1;
		int log_om1 = SZ / step;
		for (int k = 0; k < SZ; k += step) {
			int upp = k + len;
			int log_om = X;
			for (int j = k; j < upp; j++) {
				T om = opow[log_om];
				T t = mul(om, a[j + len]);
				T u = a[j];
				a[j] = add(u, t);
				a[j + len] = sub(u, t);
				log_om += Y * log_om1;
			}
		}
	}
}
