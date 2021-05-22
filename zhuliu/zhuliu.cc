/*
Zhu-Liu Algorithm
The ID of vertexes should be in [0, NV-1)
And self-cycle must be removed.
*/
#define M 600
#define type int
const type inf = (1) << 30;
struct Node {
	int u, v;
	type cost;
} E[M * M + 5];
int pre[M], ID[M], vis[M];
type In[M];
int n, m;
type Directed_MST(int root, int NV, int NE)
{
	type ret = 0;
	while (true) {
		// Find minimal in edge
		for (int i = 0; i < NV; i++)
			In[i] = inf;
		for (int i = 0; i < NE; i++) {
			int u = E[i].u;
			int v = E[i].v;
			if (E[i].cost < In[v] && u != v) {
				pre[v] = u;
				In[v] = E[i].cost;
			}
		}
		for (int i = 0; i < NV; i++) {
			if (i == root)
				continue;
			if (In[i] == inf)
				return -1; // No Solution
		}
		// Find cycle
		int cntnode = 0;
		memset(ID, -1, sizeof(ID));
		memset(vis, -1, sizeof(vis));
		In[root] = 0;
		for (int i = 0; i < NV; i++) {
			ret += In[i];
			int v = i;
			while (vis[v] != i && ID[v] == -1 && v != root) {
				vis[v] = i;
				v = pre[v];
			}
			if (v != root && ID[v] == -1) {
				for (int u = pre[v]; u != v; u = pre[u]) {
					ID[u] = cntnode;
				}
				ID[v] = cntnode++;
			}
		}
		if (cntnode == 0)
			break; // No cycle
		for (int i = 0; i < NV; i++)
			if (ID[i] == -1) {
				ID[i] = cntnode++;
			}
		// 3.Merge vertexes
		for (int i = 0; i < NE; i++) {
			int v = E[i].v;
			E[i].u = ID[E[i].u];
			E[i].v = ID[E[i].v];
			if (E[i].u != E[i].v) {
				E[i].cost -= In[v];
			}
		}
		NV = cntnode;
		root = ID[root];
	}
	return ret;
}
