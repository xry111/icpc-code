struct E {
	int v, id;
};

vector<E> G[100001];

struct Q {
	int v, xx, val;
};

vector<Q> q[100001];
int dfs(int u)
{
	vis[u] = -1;
	p[u] = a[u] = u;
	for (const E &e : G[u]) {
		if (vis[e.v])
			continue;
		e2v[e.id] = e.v;
		dfs(e.v);
		int uu = find(u), vv = find(e.v);
		p[vv] = uu;
		a[uu] = u;
	}
	vis[u] = 1;
	for (const Q &qq : q[u])
		if (vis[qq.v] == 1) {
			int vv = find(qq.v);
			mark[qq.xx][a[vv]] -= qq.val + qq.val;
			if (qq.xx == 0)
				mark[2][a[vv]] += qq.val;
		}
}
