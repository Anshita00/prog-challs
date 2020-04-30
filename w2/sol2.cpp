#include <iostream>
#include<cstring>
#include <sstream>
#include <queue>
#include <set>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

typedef tree <int , null_type , less <int >, rb_tree_tag , tree_order_statistics_node_update> ordered_set ;

int findMinimumNumberOfSwaps (int numbers[500001], int size) {
	multiset<int> st;
	int numSwaps = 0;
	int key, j;
	for (int i = 0; i < size; i++) {
		if (i != 0) {
			auto it = st.lower_bound(numbers[i]);
			int index = distance(st.begin(), it);
			numSwaps+= (i - index);
			if (*it == numbers[i]) {
				numSwaps--;
			}
		}
		st.insert(numbers[i]);
	}

	return numSwaps;
}

int main() {
	int n;
	scanf("%d",  &n);
	int nCopy = n;
	int numbers[500001];
	while (n != 0) {
		int i = 0;
		while (n--) {
			int temp;
			scanf("%d", &temp);
			numbers[i] = temp;
			i++;
		}

		printf("%d\n", findMinimumNumberOfSwaps(numbers, nCopy));
		scanf("%d",  &n);
		nCopy = n;
	}

}