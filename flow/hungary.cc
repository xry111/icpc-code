int a[101], b[101];
int g[101][101] = {0};
int mark[101] = {0};
int result[101] = {0};

bool find(int a)
{
	for (int i = 1; i <= m; i++) {
		if (g[a][i] && !mark[i]) {
			mark[i] = 1;
			if (!result[i] || find(result[i])) {
				result[i] = a;
				return true;
			}
		}
	}
	return false;
}
void hungary(int n)
{
	for (int i = 1; i <= n; i++) {
		memset(mark, 0, sizeof(mark));
		if (find(i))
			ans++;
	}
}
