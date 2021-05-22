#include <cassert>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <functional>

using namespace std;

namespace wang9897
{

using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag,
             tree_order_statistics_node_update>
    set_t;

} // namespace wang9897

using wang9897::set_t;

int main()
{
	set_t s;
	s.insert(1);
	s.insert(10);
	s.insert(100);
	s.insert(200);
	assert(*s.find_by_order(2) == 100);
	assert(s.order_of_key(100) == 2);
	assert(s.order_of_key(101) == 3);
	assert(s.order_of_key(200) == 3);
}
