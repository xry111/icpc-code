const int MAXN = 1e5 + 10;
int Ma[MAXN * 2];
int Mp[MAXN * 2];

template <class T>
void Manacher(const T *s, int len)
{
	int l = 0;
	Ma[l++] = DUMMY1;
	Ma[l++] = DUMMY2;
	for (int i = 0; i < len; i++) {
		Ma[l++] = s[i];
		Ma[l++] = DUMMY2;
	}
	Ma[l] = 0;
	int mx = 0, id = 0;
	for (int i = 1; i < l; i++) {
		Mp[i] = mx > i ? min(Mp[2 * id - i], mx - i) : 1;
		while (Ma[i + Mp[i]] == Ma[i - Mp[i]])
			Mp[i]++;
		if (i + Mp[i] > mx) {
			mx = i + Mp[i];
			id = i;
		}
	}
}
