// Copyright (C) 2004 Ami Tavory and Vladimir Dreizin, IBM-HRL.
#include <ext/pb_ds/priority_queue.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace __gnu_pbds;

// The first entry is the node's id, and the second is the distance.
typedef std::pair<size_t, size_t> pq_value;

struct pq_value_cmp : public binary_function<pq_value, pq_value, bool> {
	inline bool operator()(const pq_value &r_lhs, const pq_value &r_rhs) const
	{
		return r_rhs.second < r_lhs.second;
	}
};

int main()
{
	enum {
		num_vertices = 5,
		// "Infinity".
		graph_inf = 1000
	};
	const size_t a_a_edge_legnth[num_vertices][num_vertices] = {
	    {0, 5, 3, 7, 6},
	    {2, 0, 2, 8, 9},
	    {2, 1, 0, 8, 0},
	    {1, 8, 3, 0, 2},
	    {2, 3, 4, 2, 0}};

	// The priority queue type.
	typedef __gnu_pbds::priority_queue<pq_value, pq_value_cmp> pq_t;

	// The priority queue object.
	pq_t p;

	// This vector contains for each node, a find-iterator into the
	// priority queue.
	vector<pq_t::point_iterator> a_it;
	for (size_t i = 0; i < num_vertices; ++i)
		a_it.push_back(p.push(pq_value(i, graph_inf)));

	p.modify(a_it[0], pq_value(0, 0));

	while (!p.empty()) {
		const pq_value &r_v = p.top();
		const size_t node_id = r_v.first;
		const size_t dist = r_v.second;

		cout << "The distance from 0 to " << node_id << " is " << dist << endl;

		for (size_t neighbor_i = 0; neighbor_i < num_vertices; ++neighbor_i) {
			const size_t pot_dist = dist + a_a_edge_legnth[node_id][neighbor_i];

			if (a_it[neighbor_i] == a_it[0])
				continue;

			if (pot_dist < a_it[neighbor_i]->second)
				p.modify(a_it[neighbor_i], pq_value(neighbor_i, pot_dist));
		}

		a_it[node_id] = a_it[0];
		p.pop();
	}
	return 0;
}
