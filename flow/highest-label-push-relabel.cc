template <class Int>
struct Arc {
	int v, r;
	Int c, f;
};

template <int N, class Int = int>
struct MaxFlow {
	typedef Arc<Int> arc_t;
	vector<arc_t> G[N + 1];
	int curr[N + 1];
	int h[N + 1];
	Int e[N + 1];

	void init()
	{
		for (int i = 0; i <= N; i++)
			G[i].clear();
	}

	Int cf(int u, int arc)
	{
		return (~(G[u][arc].r)) ? G[G[u][arc].v][G[u][arc].r].f
		                        : G[u][arc].c - G[u][arc].f;
	}

	void AddEdge(int u, int v, Int c)
	{
		assert(c > 0);
		int x = G[u].size();
		G[u].push_back(arc_t{v, -1, c, 0});
		G[v].push_back(arc_t{u, x, 0, 0});
	}

	void push(int u, int arc)
	{
		int v = G[u][arc].v;
		assert(e[u] > 0);
		assert(h[u] == h[v] + 1);
		Int D = min(e[u], cf(u, arc));
		if (G[u][arc].r == -1)
			G[u][arc].f += D;
		else {
			arc = G[u][arc].r;
			G[v][arc].f -= D;
		}
		e[u] -= D;
		e[v] += D;
	}

	void relabel(int u)
	{
		int Min = INT_MAX;
		assert(e[u] > 0);
		for (int i = 0; i < G[u].size(); i++)
			if (cf(u, i))
				Min = min(Min, h[G[u][i].v]);
		assert(Min != INT_MAX);
		h[u] = Min + 1;
	}

	void discharge(int u)
	{
		while (e[u] > 0) {
			int v = G[u][curr[u]].v;
			if (curr[u] == G[u].size()) {
				relabel(u);
				curr[u] = 0;
			} else if (cf(u, curr[u]) && h[u] == h[v] + 1)
				push(u, curr[u]);
			else
				curr[u]++;
		}
	}

	list<int> L[N + N];

	Int solve(int s, int t)
	{
		memset(h, 0, sizeof(h));
		memset(e, 0, sizeof(e));
		memset(curr, 0, sizeof(curr));
		for (int i = 0; i < N + N; i++)
			L[i].clear();

		// Use BFS to initialize the height.
		queue<int> Q;
		Q.push(t);
		fill(h, h + N + 1, N + N);
		h[t] = 0;
		while (!Q.empty()) {
			int u = Q.front();
			Q.pop();
			for (typename vector<arc_t>::iterator it = G[u].begin();
			     it != G[u].end(); it++)
				if (h[it->v] == N + N) {
					Q.push(it->v);
					h[it->v] = h[u] + 1;
					if (it->v != s)
						L[h[it->v]].push_back(it->v);
				}
		}
		h[s] = N;

		// Preflow
		for (int i = 0; i <= N; i++)
			for (typename vector<arc_t>::iterator it = G[i].begin();
			     it != G[i].end(); it++)
				it->f = 0;
		for (typename vector<arc_t>::iterator it = G[s].begin();
		     it != G[s].end(); it++) {
			e[it->v] += it->f = it->c;
			e[s] -= it->f;
		}

		for (int level = N - 1; level >= 0; level--) {
			for (list<int>::iterator it = L[level].begin();
			     it != L[level].end(); it++) {
				int u = *it;
				int old = h[u];
				discharge(u);
				if (h[u] != old) {
					// Gap Optimize
					if (level > 0 && L[level].size() == 1) {
						for (int k = level + 1; k <= N; k++)
							L[N + 1].splice(L[N + 1].begin(), L[k]);
						for (list<int>::iterator it = L[N + 1].begin();
						     it != L[N + 1].end(); it++)
							h[*it] = N + 1;
					}
					L[h[u]].push_front(u);
					L[level].erase(it);
					level = h[u];
					break;
				}
			}
		}

		return e[t];
	}
};
