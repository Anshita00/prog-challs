#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <utility>
#include <limits>
#include <algorithm>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

const int MAXN = 200001;
ordered_set rt[4*MAXN];
int totId = 0;
int indexInRangeTree[MAXN], startRange[MAXN], endRange[MAXN];
vector<int> children[MAXN];
bool visited[MAXN];
int N;

void init(int n) {
	for (int i = 1; i <= n + 1; i++) {
		rt[i] = {};
	}
}

void update(int a, int v, int i = 1, int start = 1, int end = N +1) {
	if (end - start == 1) {
		rt[i].insert(v);
		return;
	}

	int mid = (start + end)/2;
	if (a < mid) update(a, v, i*2, start, mid);
	else update(a,v, i*2 +1, mid, end);
	rt[i].insert(v);
}

int query(int a, int b, int val, int i = 1, int start = 1, int end = N +1) {
	if (start == a && end == b) {
		return rt[i].order_of_key(val);
	}

	int mid = (start + end)/2;
	int answer = 0;

	if (a < mid) answer += query(a, min(b, mid), val, i * 2, start, mid);
	if (b > mid) answer += query(max(a, mid), b, val, i * 2 + 1, mid, end);
	return answer;

}

void computeTreeRanges(int c) {
	if (visited[c]) return;
	indexInRangeTree[c] = startRange[c] = totId++;
	visited[c] = true;
	for (int nxt: children[c]) {
		computeTreeRanges(nxt);
	}
	endRange[c] = totId;
}

int main() {
	int Q;
	int sizes[MAXN];
	scanf("%d %d", &N, &Q);

	for (int i = 0; i < N; i++) {
		int temp;
		scanf("%d", &temp);
		sizes[i] = temp;
		visited[i] = false;
	}
	init(N);

	for (int i = 0; i < N - 1; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		children[u].push_back(v);
		children[v].push_back(u);
	}

	computeTreeRanges(0);

	for (int i = 0; i < N; i++) {
		update(indexInRangeTree[i] + 1, sizes[i]);
	}

	for (int i = 0; i < Q; i++) {
		int node, value;
		scanf("%d %d", &node, &value);
		printf("%d\n", query(startRange[node] + 1, endRange[node] + 1, value));
		update(indexInRangeTree[node] + 1, value);
	}

}