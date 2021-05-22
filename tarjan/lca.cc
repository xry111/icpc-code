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
	for (vector<E>::iterator it = G[u].begin(); it != G[u].end(); it++) {
		if (vis[it->v])
			continue;
		e2v[it->id] = it->v;
		dfs(it->v);
		int uu = find(u), vv = find(it->v);
		p[vv] = uu;
		a[uu] = u;
	}
	vis[u] = 1;
	for (vector<Q>::iterator it = q[u].begin(); it != q[u].end(); it++)
		if (vis[it->v] == 1) {
			int vv = find(it->v);
			mark[it->xx][a[vv]] -= it->val + it->val;
			if (it->xx == 0)
				mark[2][a[vv]] += it->val;
		}
}
