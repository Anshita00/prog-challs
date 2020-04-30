#include <iostream>
#include<cstring>
#include <sstream>
#include <queue>
#include<map>
#include <algorithm> 

using namespace std;

struct node {
	long long value;
	unsigned int index;
};

const unsigned int MAXVAL = 100001;
node tree[266666];

unsigned int max (unsigned int a, unsigned int b) {
	if (a > b) {
		return a;
	}
	return b;
}

void update (unsigned int a, node v, unsigned long i = 1, unsigned int start = 1, unsigned int end = MAXVAL) {
	if (end - start == 1) {
		tree[i] = v;
		return;
	}

	unsigned int mid = ( start + end ) / 2;
	if (a < mid ) 
		update (a, v, i * 2, start , mid);
	else
		update (a, v,i * 2 + 1, mid , end);

	tree[i] = tree [i*2].value < tree [i*2+1].value ? tree[i*2+1] : tree[i*2];
}

node query (unsigned int a, unsigned int b, unsigned long i = 1, unsigned int start = 1, unsigned int end = MAXVAL ) {

	if ( start == a && end == b) return tree[i];
	// we might need to query one or both of the children
	unsigned int mid = ( start + end ) / 2;
	node answer;
	answer.value = 0;
	answer.index = -1;
	// the left child can query [a , mid )
	if (a < mid ) answer = query (a,min (b, mid), i * 2 , start , mid );
	// the right child can query [mid , b)
	if (b > mid) {
		node tempResult = query(max(a, mid),b, i * 2 + 1, mid , end );
		answer = tempResult.value >  answer.value ? tempResult : answer;
	}
	return answer ;
}
int main() {

	unsigned int n;
	long long d;
	map<long long, unsigned int> heightsCompressed;
	map <unsigned int, unsigned int> prevs;
	vector<long long> heights;
	long long heightsCopy[100000];

	scanf("%u %lld", &n, &d);

	for (unsigned int i = 0; i < 266666; i++) {
		node temp;
		temp.value = 0;
		temp.index = 1;
		tree[i] = temp;
	}

	for (unsigned int i = 0; i < n; i++) {
		long long h;
		scanf("%lld", &h);
		heights.push_back(h);
		heightsCopy[i] = h;
	}

	sort(heightsCopy, heightsCopy + n);

	for (unsigned int i = 0; i < n; i++) {
		heightsCompressed.insert({ heightsCopy[i], i+1 });
	}
	int i = 1;
	for (auto it = heights.begin(); it != heights.end(); it++) {
		long long height = *it;
		node best;
		best.value = 0;
		best.index = 1;
		if (height - d >= 1) {
			auto result = heightsCompressed.lower_bound(height - d);
			if (result->first >height -d) {
				best = query(1,result->second);
			} else {
				best = query(1,result->second+1);	
			}
			// printf("Result second in first if %u\n", result->second);
		}
		if (height + d <= 1000000000000000) {
			auto result = heightsCompressed.lower_bound(height + d);
			// printf("Result first and second in second if %lld %u\n", result->first, result->second);
			if (result->second <= n + 1 && result->second >= 1) {
				node tempBest = query(result->second, MAXVAL);
				best = best.value > tempBest.value ? best : tempBest;
			} 
		}
		auto result = heightsCompressed.find(height);
		// printf("Result first second last %lld %u\n", result->first, result->second);
		best.value = best.value + 1;
		prevs.insert({ i, best.index });
		best.index = i;
		update(result->second, best);
		i++;
	}

	node lastQuery = query(1, n+1);
	printf("%lld\n", lastQuery.value);
	vector<unsigned int> indices;
	indices.push_back(lastQuery.index);
	auto first = prevs.find(lastQuery.index);
	i = 0;
	while (i < lastQuery.value - 1) {
		// printf("first and second %u %u\n", first->first, first->second);
		indices.push_back(first->second);
		first = prevs.find(first->second);
		i++;
	}
	reverse(indices.begin(), indices.end());
	for (auto it = indices.begin(); it != indices.end(); ++it) {
		printf("%u ", *it);
	}	
	// for (auto it = bests.begin(); it != bests.end(); ++it) {
	// 	printf("%u ", *it);
	// }

	printf("\n");
	return 0;
}