int discrete_log(int a, int b, int M)
{
	if (M == 1)
		return 0;
	b %= M;
	a %= M;
	if (b == 1)
		return 0;

	int g = __gcd(a, M);
	if (g == 1)
		return BSGS(a, b, M);

	int F = M;
	for (int p : prime)
		if (g % p == 0) {
			while (g % p == 0)
				g /= p;
			while (F % p == 0)
				F /= p;
		}
	if (g != 1)
		while (F % g == 0)
			F /= g;
	int G = M / F;

	if (b % G == 0) {
		long long t = 1, i;
		for (i = 0; t != 0; i++)
			t = t * a % G;
		int A = BSGS(a, b, F);
		if (A == -1)
			return -1;
		int T = phi(F);
		int T1 = T;
		for (int j = 1; j * j <= T; j++)
			if (T % j == 0) {
				if (mod_pow(a, j, F) == 1)
					T1 = min(T1, j);
				if (mod_pow(a, T / j, F) == 1)
					T1 = min(T1, T / j);
			}
		while (A < i)
			A += T1;
		return A;
	} else {
		long long t = 1;
		for (int i = 0; t != 0; i++) {
			if (t == b % G)
				return mod_pow(a, i, M) == b ? i : -1;
			t = t * a % G;
		}
		return -1;
	}
}
