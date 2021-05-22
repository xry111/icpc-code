template <int N1, int N2>
struct HK {
	int n;
	int dis1[N1], dis2[N2], mate1[N1], mate2[N2];
	vector<int> G[N1];
	vector<int> Gr[N2];

	void addEdge(int u, int v)
	{
		if (u == -1 || v == -1)
			return;
		G[u].push_back(v);
		Gr[v].push_back(u);
	}

	bool bfs()
	{
		static queue<int> q;
		memset(dis1, 0, sizeof(dis1));
		memset(dis2, 0, sizeof(dis2));
		for (int i = 0; i < n; i++)
			if (mate1[i] == -1)
				q.push(i);
		bool ret = 0;
		while (!q.empty()) {
			int u = q.front();
			q.pop();
			for (vector<int>::iterator it = G[u].begin(); it != G[u].end();
			     it++) {
				int v = *it;
				if (dis2[v] == 0) {
					dis2[v] = dis1[u] + 1;
					if (mate2[v] == -1)
						ret = 1;
					else {
						dis1[mate2[v]] = dis2[v] + 1;
						q.push(mate2[v]);
					}
				}
			}
		}
		return ret;
	}

	bool dfs(int u)
	{
		for (vector<int>::iterator it = G[u].begin(); it != G[u].end(); it++) {
			int v = *it;
			if (dis1[u] + 1 == dis2[v]) {
				dis2[v] = 0;
				if (mate2[v] == -1 || dfs(mate2[v])) {
					mate1[u] = v;
					mate2[v] = u;
					return 1;
				}
			}
		}
		return 0;
	}

	void init(int _n1, int _n2)
	{
		n = _n1;
		for (int i = 0; i < n; i++)
			G[i].clear();
		for (int i = 0; i < _n2; i++)
			Gr[i].clear();
	}

	int solve()
	{
		memset(mate1, -1, sizeof(mate1));
		memset(mate2, -1, sizeof(mate2));
		int ans = 0;
		while (bfs())
			for (int i = 0; i < n; i++)
				if (mate1[i] == -1 && dfs(i))
					ans++;
		return ans;
	}
};
