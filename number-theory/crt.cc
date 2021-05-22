long long crt(const int d[], const int ans[], int cnt, int MAXANS)
{
	long long ans0 = 0, d0 = 1;
	int checking = 0;
	for (int i = 0; i < cnt; i++) {
		long long d1 = d[i], ans1 = ans[i];

		if (checking) {
			if (ans0 % d1 == ans1) {
				continue;
			}
			return -1;
		}

		if (ans1 < ans0) {
			swap(ans1, ans0);
			swap(d1, d0);
		}
		long long A = d0, B = ans1 - ans0, N = d1;

		long long g = gcd(A, N);
		if (B % g) {
			return -1;
		}
		A /= g;
		N /= g;
		B /= g;
		long long x = (inv(A, N) * B) % N;
		ans0 += d0 * x;
		d0 = lcm(d0, d1);

		if (d0 > MAXANS) {
			if (ans0 > MAXANS) {
				return -1;
			} else {
				checking = 1;
			}
		}
	}
	return ans0;
}
