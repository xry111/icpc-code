static stack<int> st;
static void dfs(int u)
{ // Call for every vertex not visited
	dfn[u] = low[u] = ++clk;
	st.push(u);
	ins[u] = 1;
	for (int v : G[u])
		if (!dfn[v]) {
			dfs(v);
			low[u] = min(low[u], low[v]);
		} else if (ins[v])
			low[u] = min(low[u], dfn[v]);
	if (dfn[u] == low[u]) {
		// get a scc
		int v;
		do {
			v = st.top();
			st.pop();
			ins[v] = 0;
			// v belongs to this scc
		} while (u != v);
	}
}
