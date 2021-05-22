multiset<int> s;
multiset<int>::iterator it;

//...

for (int i = 0; i < n; i++) {
	s.insert(a[i]);

	// non-decrese:
	it = s.upper_bound(a[i]);
	// for strictly increase:
	// it = s.lower_bound(a[i]);
	// it++;

	if (it != s.end())
		s.erase(it);
}

cout << s.size() << endl;
