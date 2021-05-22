#include <bits/stdc++.h>
using namespace std;

#define LLD "%lld"

int fact[10007];

typedef long long ll;
void exgcd(ll a, ll b, ll &g, ll &x, ll &y)
{
	if (!b) {
		x = 1;
		y = 0;
		g = a;
	} else {
		exgcd(b, a % b, g, y, x);
		y -= x * (a / b);
	}
}

ll inv(ll a, ll n)
{
	ll d, x, y;
	exgcd(a, n, d, x, y);
	return d == 1 ? (x + n) % n : -1;
}

inline long long cnt_10007(long long x)
{
	static const long long A = 10007, B = 10007LL * 10007, C = A * B, D = B * B;
	return x / A + x / B + x / C + x / D;
}

long long fact_expect_10007(long long x)
{
	if (!x)
		return 1LL;
	long long ret = fact[x % 10007];
	ret = (ret * fact_expect_10007(x / 10007)) % 10007;
	return ((x / 10007) & 1) ? (ret * 10006) % 10007 : ret;
}

int main()
{
	fact[0] = 1;
	for (int i = 1; i < 10007; i++) {
		fact[i] = (fact[i - 1] * i) % 10007;
	}
	long long n, m;
	while (scanf(LLD LLD, &n, &m) == 2) {
		if (cnt_10007(m) > cnt_10007(n) + cnt_10007(m - n))
			puts("0");
		else {
			long long ans = fact_expect_10007(m);
			ans = ans * inv(fact_expect_10007(n), 10007);
			ans = ans % 10007;
			ans = ans * inv(fact_expect_10007(m - n), 10007);
			ans = ans % 10007;
			printf(LLD "\n", ans);
		}
	}
	return 0;
}
