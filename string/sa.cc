static int sa[1000000], _rk[2][1000000];
static int id[1000000];
static int rk_id[1000000];
static int *rk;
static int cnt[1000000];

static void suffix_sort(const string &s)
{
	// We will swap pointers instead of copying the buffers to save CPU
	// time.  See https://icpc.xidian.wiki/cce/swap-array.
	rk = _rk[0];
	int *new_rk = _rk[1];

	// Initialize sa and rk arrays (result 1).
	int range_rk = 26;
	fill(cnt, cnt + 26, 0);
	int l = s.size();
	for (int i = 0; i < l; i++) {
		rk[i] = s[i] - 'a';
		cnt[rk[i]] += 1;
	}
	for (int i = 1; i < 26; i++)
		cnt[i] += cnt[i - 1];
	for (int i = l - 1; i >= 0; i--) {
		cnt[rk[i]] -= 1;
		sa[cnt[rk[i]]] = i;
	}

	// $\log w$ doubling passes (result w -> 2w)
	for (int w = 1; w < l; w <<= 1) {
		int p = 0;
		// First radix sorting pass, sort [0, i) by rk[. + w] and store
		// the result into id.
		for (int i = 1; i <= w; i++)
			id[p++] = l - i;
		for (int i = 0; i < l; i++)
			if (sa[i] >= w)
				id[p++] = sa[i] - w;
		// Cache rk[id[.]] to avoid rogue memory access patterns.
		for (int i = 0; i < l; i++)
			rk_id[i] = rk[id[i]];
		// Second radix sorting pass, stably sort id (with counting sort)
		// and store the result into sa.
		fill(cnt, cnt + range_rk, 0);
		for (int i = 0; i < l; i++)
			cnt[rk_id[i]] += 1;
		for (int i = 1; i < range_rk; i++)
			cnt[i] += cnt[i - 1];
		for (int i = l - 1; i >= 0; i--) {
			cnt[rk_id[i]] -= 1;
			sa[cnt[rk_id[i]]] = id[i];
		}
		// Update rk using just-updated sa.  Same substrings should be
		// mapped to same rk or the stability of sort will be broken.
		p = 0;
		new_rk[sa[0]] = 0;
		for (int i = 1; i < l; i++) {
			int a = sa[i], b = sa[i - 1];
			int x = (a + w < l ? rk[a + w] : -1);
			int y = (b + w < l ? rk[b + w] : -1);
			if (rk[a] != rk[b] || x != y)
				p++;
			new_rk[sa[i]] = p;
		}
		swap(new_rk, rk);
		range_rk = p + 1;
		// Fast path to exit when all substrings are already distinct.
		if (range_rk == l)
			break;
	}
	// Verification.  Do NOT define DEBUG in submission code.
#if DEBUG
	for (int i = 0; i < l; i++)
		assert(sa[rk[i]] == i);
	for (int i = 1; i < l; i++) {
		int p = sa[i], q = sa[i - 1];
		assert(s.substr(p, l - p) > s.substr(q, l - q));
	}
#endif
}
