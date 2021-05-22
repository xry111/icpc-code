void dfs1(int u)
{
	cnt[u] = 1;
	maxch[u] = 0;
	int Max = -1;
	for (const E &e : G[u]) {
		int v = e.v;
		if (cnt[v] == 0) {
			e2v[e.id] = v;
			dep[v] = dep[u] + 1;
			par[v] = u;
			val[v] = e.c;
			dfs1(v);
			cnt[u] += cnt[v];
			if (Max < cnt[v]) {
				Max = cnt[v];
				maxch[u] = v;
			}
		}
	}
}

int top[200001], idx[200001] = {0}, clk;

void dfs2(int u, int t)
{
	idx[u] = ++clk;
	top[u] = t;
	if (maxch[u])
		dfs2(maxch[u], t);
	for (const E &e : G[u])
		if (!idx[e.v])
			dfs2(e.v, e.v);
}

void hld_query(int u, int v)
{
	while (top[u] != top[v]) {
		if (dep[top[u]] < dep[top[v]])
			swap(u, v);
		// Query interval [ idx[top[u], idx[u] ].
		ret = mul(ret, sgt_query(idx[top[u]], idx[u]));
		u = par[top[u]];
	}
	if (dep[u] > dep[v])
		swap(u, v);
	// Query interval [ idx[u], idx[v] ].
	return;
}
