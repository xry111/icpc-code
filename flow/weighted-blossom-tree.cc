#include <bits/stdc++.h>
using namespace std;

template <class T, int V>
struct weighted_blossom_tree {
	enum { N = V * 2 };
	static const T inf = numeric_limits<T>::max() >> 1;
	struct Q {
		int u, v;
		T w;
	} e[N][N];
	T lab[N];

	inline T d(const Q &x)
	{
		return lab[x.u] + lab[x.v] - e[x.u][x.v].w * 2;
	}

	int n, m, id, h, t;
	int lk[N], sl[N], st[N], f[N], b[N][N], s[N], ed[N], q[N];
	vector<int> p[N];
	void upd(int u, int v)
	{
		if (!sl[v] || d(e[u][v]) < d(e[sl[v]][v]))
			sl[v] = u;
	}
	void ss(int v)
	{
		sl[v] = 0;
		for (int u = 1; u <= n; u++)
			if (e[u][v].w > 0 && st[u] != v && !s[st[u]])
				upd(u, v);
	}
	void ins(int u)
	{
		if (u <= n)
			q[++t] = u;
		else
			for (int v : p[u])
				ins(v);
	}
	void mdf(int u, int w)
	{
		st[u] = w;
		if (u > n)
			for (int v : p[u])
				mdf(v, w);
	}
	int gr(int u, int v)
	{
		v = find(p[u].begin(), p[u].end(), v) - p[u].begin();
		if (v & 1) {
			reverse(p[u].begin() + 1, p[u].end());
			return (int)p[u].size() - v;
		}
		return v;
	}
	void stm(int u, int v)
	{
		lk[u] = e[u][v].v;
		if (u <= n)
			return;
		Q w = e[u][v];
		int x = b[u][w.u], y = gr(u, x);
		for (int i = 0; i < y; i++)
			stm(p[u][i], p[u][i ^ 1]);
		stm(x, v);
		rotate(p[u].begin(), p[u].begin() + y, p[u].end());
	}
	void aug(int u, int v)
	{
		int w = st[lk[u]];
		stm(u, v);
		if (!w)
			return;
		stm(w, st[f[w]]);
		aug(st[f[w]], w);
	}
	int lca(int u, int v)
	{
		for (++id; u || v; swap(u, v)) {
			if (!u)
				continue;
			if (ed[u] == id)
				return u;
			ed[u] = id;
			if (u = st[lk[u]])
				u = st[f[u]];
		}
		return 0;
	}
	void add(int u0, int a, int v)
	{
		int x = n + 1, i, j;
		while (x <= m && st[x])
			++x;
		if (x > m)
			++m;
		lab[x] = s[x] = st[x] = 0;
		lk[x] = lk[a];
		p[x].clear();
		p[x].push_back(a);
		for (i = u0; i != a; i = st[f[j]]) {
			p[x].push_back(i);
			j = st[lk[i]];
			p[x].push_back(j);
			ins(j);
		}
		reverse(p[x].begin() + 1, p[x].end());
		for (i = v; i != a; i = st[f[j]]) {
			p[x].push_back(i);
			j = st[lk[i]];
			p[x].push_back(j);
			ins(j);
		}
		mdf(x, x);
		for (i = 1; i <= m; i++)
			e[x][i].w = e[i][x].w = 0;
		memset(b[x] + 1, 0, n * sizeof b[0][0]);
		for (int u : p[x]) {
			for (v = 1; v <= m; v++)
				if (!e[x][v].w || d(e[u][v]) < d(e[x][v])) {
					e[x][v] = e[u][v];
					e[v][x] = e[v][u];
				}
			for (v = 1; v <= n; v++)
				if (b[u][v])
					b[x][v] = u;
		}
		ss(x);
	}
	void ex(int u)
	{
		assert(s[u] == 1);
		for (int x : p[u])
			mdf(x, x);
		int a = b[u][e[u][f[u]].u];
		int r = gr(u, a);
		for (int i = 0; i < r; i += 2) {
			int x = p[u][i], y = p[u][i + 1];
			f[x] = e[y][x].u;
			s[x] = 1;
			s[y] = 0;
			sl[x] = 0;
			ss(y);
			ins(y);
		}
		s[a] = 1;
		f[a] = f[u];
		for (int i = r + 1; i < p[u].size(); i++) {
			s[p[u][i]] = -1;
			ss(p[u][i]);
		}
		st[u] = 0;
	}
	bool on(const Q &e)
	{
		int u = st[e.u], v = st[e.v], a;
		if (s[v] == -1) {
			f[v] = e.u;
			s[v] = 1;
			a = st[lk[v]];
			sl[v] = sl[a] = s[a] = 0;
			ins(a);
		} else if (!s[v]) {
			a = lca(u, v);
			if (!a) {
				aug(u, v);
				aug(v, u);
				return true;
			} else
				add(u, a, v);
		}
		return false;
	}
	bool bfs()
	{
		fill(s + 1, s + 1 + m, -1);
		fill(sl + 1, sl + 1 + m, 0);
		h = 1;
		t = 0;
		int i;
		for (i = 1; i <= m; i++)
			if (st[i] == i && !lk[i]) {
				f[i] = s[i] = 0;
				ins(i);
			}
		if (h > t)
			return 0;
		while (1) {
			while (h <= t) {
				int u = q[h++];
				if (s[st[u]] != 1)
					for (int v = 1; v <= n; v++)
						if (e[u][v].w > 0 && st[u] != st[v]) {
							if (d(e[u][v]))
								upd(u, st[v]);
							else if (on(e[u][v]))
								return true;
						}
			}
			T x = inf;
			for (i = n + 1; i <= m; i++)
				if (st[i] == i && s[i] == 1)
					x = min(x, lab[i] >> 1);
			for (i = 1; i <= m; i++)
				if (st[i] == i && sl[i] && s[i] != 1)
					x = min(x, d(e[sl[i]][i]) >> s[i] + 1);
			for (i = 1; i <= n; i++)
				if (s[st[i]] != -1)
					if ((lab[i] += (s[st[i]] * 2 - 1) * x) <= 0)
						return false;
			for (i = n + 1; i <= m; i++)
				if (st[i] == i && s[st[i]] != -1)
					lab[i] += (2 - s[st[i]] * 4) * x;
			h = 1;
			t = 0;
			for (i = 1; i <= m; i++)
				if (st[i] == i && sl[i] && st[sl[i]] != i && !d(e[sl[i]][i]) &&
				    on(e[sl[i]][i]))
					return true;
			for (i = n + 1; i <= m; i++)
				if (st[i] == i && s[i] == 1 && !lab[i])
					ex(i);
		}
		return false;
	}

	typedef tuple<int, int, T> E;
	T max_weighted_general_match(int x, const vector<E> &edges)
	{
		n = m = x;
		memset(ed + 1, 0, m * sizeof ed[0]);
		memset(lk + 1, 0, m * sizeof lk[0]);
		id = 0;
		iota(st + 1, st + n + 1, 1);
		int i, j;
		T wm = 0;
		T r = 0;
		for (i = 1; i <= n; i++)
			for (j = 1; j <= n; j++)
				e[i][j] = {i, j, 0};
		for (auto [u, v, w] : edges) {
			e[v][u].w = e[u][v].w = max(e[u][v].w, w);
			wm = max(wm, w);
		}
		for (i = 1; i <= n; i++)
			p[i].clear();
		for (i = 1; i <= n; i++)
			for (j = 1; j <= n; j++)
				b[i][j] = i * (i == j);
		fill_n(lab + 1, n, wm);
		while (bfs())
			;
		for (i = 1; i <= n; i++)
			if (lk[i])
				r += e[i][lk[i]].w;
		return r / 2;
	}
};

#ifdef UOJ81
weighted_blossom_tree<long long, 400> wbt;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n, m;
	cin >> n >> m;
	vector<tuple<int, int, long long>> edges(m);
	for (auto &[u, v, w] : edges)
		cin >> u >> v >> w;
	cout << wbt.max_weighted_general_match(n, edges) << '\n';
	for (int i = 1; i <= n; i++)
		cout << wbt.lk[i] << " \n"[i == n];
}
#endif
