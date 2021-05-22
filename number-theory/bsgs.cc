#if __cplusplus < 201103L
#include <ext/hash_map>
using __gnu_cxx::hash_map;
#define unordered_map hash_map
#endif

int BSGS(int a, int b, int M)
{
	assert(__gcd(a, M) == 1); /* a = 2, b = 3, M = 100 */
	if (M == 1)
		return 0;
	b %= M;
	a %= M;
	if (b == 1)
		return 0;
	int step = sqrt(M) + 1;
	long long x = 1, p = 1;
	unordered_map<int, int> mp;
	for (int i = 0; i < step; i++) {
		mp[p * b % M] = i;
		p = p * a % M;
	}
	for (int i = step; i <= step * step; i += step) {
		unordered_map<int, int>::iterator it = mp.find(x = x * p % M);
		if (it != mp.end())
			return i - it->second;
	}
	return -1;
}
