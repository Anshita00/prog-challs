#include <iostream>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <set>
#include <queue>
#include <map>
#include <utility>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define MAXK 10
#define MAXN 1000000
#define MOD 1000000007

using namespace std;
using namespace __gnu_pbds;

typedef tree<long long, null_type, less<long long>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

ordered_set numMultiples[MAXN+1];

void init() {
	for (int i = 1; i <= MAXN; i++) {
		for (int j = i; j <= MAXN; j+=i) {
			numMultiples[i].insert(j);
		}
	}
}



int main() {

	int T;
	init();
	while (T--) {
		scanf("%d", &N);
	}


	return 0;
}