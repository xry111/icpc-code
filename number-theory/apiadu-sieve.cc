const int threshold = 1000000;

bool check[threshold];
long long phi[threshold];
int prime[threshold], tot = 0;

long long sum_phi(int n)
{
	if (n < threshold)
		return phi[n];

	static map<int, long long> mp;
	auto it = mp.find(n);
	if (it != mp.end())
		return it->second;

	long long ans = n * (1ll + n) / 2;
	for (int d = 2; d <= n;) {
		int q = n / d;
		int ne = n / q + 1;
		ans -= (ne - d) * sum_phi(q);
		d = ne;
	}
	return mp[n] = ans;
}
