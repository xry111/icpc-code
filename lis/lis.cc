multiset<int> s;

//...

for (int i = 0; i < n; i++) {
	s.insert(a[i]);

	// non-decrese:
	auto it = s.upper_bound(a[i]);
	// for strictly increase:
	// auto it = s.lower_bound(a[i]);
	// it++;

	if (it != s.end())
		s.erase(it);
}

cout << s.size() << endl;
