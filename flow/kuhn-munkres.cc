#include <bits/stdc++.h>
using namespace std;

int w[401][401] = {0};
int visx[401] = {0}, visy[401] = {0};
int lx[401] = {0}, ly[401] = {0};
int linky[401] = {0};
int used[401];
int slack[401];
int fa[401];
int n;

bool find(int y0)
{
	visy[y0] = 1;
	int x = linky[y0];
	visx[x] = 1;
	if (!x) {
		while (y0 != 0) {
			linky[y0] = linky[fa[y0]];
			y0 = fa[y0];
		}
		return true;
	}
	for (int y = 1; y <= n; y++) {
		if (visy[y])
			continue;
		int t = lx[x] + ly[y] - w[x][y];
		if (!t) {
			visy[y] = 1;
			fa[y] = y0;
			if (find(y))
				return true;
		} else if (slack[y] > t) {
			slack[y] = t;
			fa[y] = y0;
		}
	}
	return false;
}

int main()
{
	int nl, nr, m;
	scanf("%d%d%d", &nl, &nr, &m);
	n = max(nl, nr);

	for (int i = 0; i < m; i++) {
		int v, u, w1;
		scanf("%d%d%d", &v, &u, &w1);
		w[v][u] = w1;
	}

	for (int i = 1; i <= nl; i++)
		for (int j = 1; j <= nr; j++)
			lx[i] = max(lx[i], w[i][j]);

	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++)
			fa[i] = 0;
		for (int i = 1; i <= n; i++)
			visx[i] = 0;
		for (int i = 1; i <= n; i++)
			visy[i] = 0;
		for (int i = 1; i <= n; i++)
			slack[i] = INT_MAX;
		linky[0] = k;
		int fr = 0;
		while (1) {
			if (find(fr))
				break;
			int gap = INT_MAX;
			for (int i = 1; i <= n; i++)
				if (visy[i] == 0 && gap > slack[i]) {
					gap = slack[i];
					fr = i;
				}
			for (int i = 1; i <= n; i++)
				if (visx[i])
					lx[i] -= gap;
			for (int i = 1; i <= n; i++)
				if (visy[i])
					ly[i] += gap;
				else
					slack[i] -= gap;
		}
	}

	int ans[401] = {0};
	long long tot = 0;
	for (int i = 1; i <= nr; i++)
		if (linky[i] != 0 && w[linky[i]][i] > 0) {
			ans[linky[i]] = i;
			tot += w[linky[i]][i];
		}
	printf("%lld\n", tot);
	for (int i = 1; i <= nl; i++)
		printf("%d%c", ans[i], " \n"[i == nl]);
	return 0;
}
