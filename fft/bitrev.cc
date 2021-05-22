template <class T>
void change(T *a, int n)
{
	int i, j, k;
	for (i = 1, j = n >> 1; i < n - 1; i++) {
		if (i < j)
			swap(a[i], a[j]);
		k = n >> 1;
		while (j >= k) {
			j -= k;
			k /= 2;
		}
		if (j < k)
			j += k;
	}
}
