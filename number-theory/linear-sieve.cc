memset(check, 0, sizeof(check));
int tot = 0;
/* Initialize foo[1]. */
for (int i = 2; i <= N; i++) {
	if (!check[i]) {
		prime[tot++] = i;
		/* Calculate foo[p]. */
	}
	for (int j = 0; j < tot; j++) {
		if (i * prime[j] > N)
			break;
		check[i * prime[j]] = 1;
		/* Calculate foo[i*prime[j]] with foo[i] and foo[prime[j]]. */
		if (i % prime[j] == 0)
			break;
	}
}
