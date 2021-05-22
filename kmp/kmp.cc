kmp[0] = kmp[1] = 0;
for (int i = 2, j = 0; i <= n; i++) {
	while (j > 0 && s[j] != s[i - 1])
		j = kmp[j];
	if (s[j] == s[i - 1])
		j++;
	kmp[i] = j;
}
