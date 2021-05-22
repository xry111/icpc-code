vector<int> G[100001];
int low[100001], dfn[100001], clk = 0;
stack<pair<int, int>, vector<pair<int, int>>> st;
int bcc_pos[100001];
int iscutv[100001];
vector<int> bcc[100001];
int num;

void dfs(int u, int p = -1)
{
	low[u] = dfn[u] = ++clk;
	int cnt = 0;
	for (int i = 0; i < (int)G[u].size(); i++) {
		int v = G[u][i];
		if (dfn[v] && dfn[v] < dfn[u] && v != p) {
			st.push({u, i});
			low[u] = min(low[u], dfn[v]);
			continue;
		}
		if (!dfn[v]) {
			cnt++;
			st.push({u, i});
			dfs(v, u);
			low[u] = min(low[u], low[v]);
			if (low[v] >= dfn[u]) {
				num++;
				iscutv[u] = 1;
				while (1) {
					int uu = st.top().first;
					int k = st.top().second;
					int vv = G[uu][k];
					st.pop();
					if (bcc_pos[uu] != num) {
						bcc_pos[uu] = num;
						bcc[num].push_back(uu);
					}
					if (bcc_pos[vv] != num) {
						bcc_pos[vv] = num;
						bcc[num].push_back(vv);
					}
					if (uu == u && k == i)
						break;
				}
			}
		} else if (v != p)
			low[u] = min(low[u], dfn[v]);
	}
	if (p < 0 && cnt == 1)
		iscutv[u] = 0;
	else if (cnt == 0)
		iscutv[u] = 1;
}
