#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

struct elemtype {
	int u, v;
	bool operator<(const elemtype &rhs) const
	{
		return v < rhs.v;
	}
};

template <class Const_Node_It, class Node_It, class Cmp_Fn, class Allocator>
struct node_update {
	typedef int metadata_type; // Maximal u in this subtree.

	elemtype minv(int u0)
	{
		Const_Node_It nd_it = node_begin(), end_it = node_end();

		while (nd_it != end_it) {
			Const_Node_It l_nd_it = nd_it.get_l_child();
			if (l_nd_it != end_it && l_nd_it.get_metadata() >= u0)
				nd_it = l_nd_it;
			else if ((*nd_it)->u >= u0)
				return **nd_it;
			else
				nd_it = nd_it.get_r_child();
		}

		return elemtype{-1, -1};
	}

	inline void operator()(Node_It nd_it, Const_Node_It end_it)
	{
		int tmp = (*nd_it)->u;
		Node_It l_nd_it = nd_it.get_l_child(), r_nd_it = nd_it.get_r_child();
		if (l_nd_it != end_it)
			tmp = max(tmp, l_nd_it.get_metadata());
		if (r_nd_it != end_it)
			tmp = max(tmp, r_nd_it.get_metadata());
		const_cast<int &>(nd_it.get_metadata()) = tmp;
	}

	virtual Const_Node_It node_begin() const = 0;
	virtual Const_Node_It node_end() const = 0;
	virtual ~node_update()
	{
	}
};

typedef tree<elemtype, null_type, less<elemtype>, rb_tree_tag, node_update>
    set_t;
