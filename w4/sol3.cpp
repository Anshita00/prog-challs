#include <iostream>
#include<cstring>
#include <sstream>
#include <queue>

using namespace std;

#define MAXN 300000
#define MOD 1000000007

struct node {
	long long s;
	long long k;
};

int totId = 1;
int N, Q;
int indexInRangeTree[MAXN + 5], startRange[MAXN+5], endRange[MAXN+5];
node rangeTree[4*MAXN+5];
vector<int> children[MAXN+5];
int depth[MAXN+5];
vector<int> edges[MAXN+5];

void init() {
	for (int i = 0; i <= N + 1; i++) {
		rangeTree[i] = { 0, 0 } ;
	}
}

void compute_tree_ranges(int c, int d) {
	indexInRangeTree[c] = startRange[c] = totId;
	depth[totId] = d;
	totId++;
	for (int nxt : edges[c]) {
		compute_tree_ranges(nxt, d + 1);
	}
	endRange[c] = totId;
}

// void constructTree(int c, int d) {
// 	depth[c] = d;
// 	for (int nxt : edges[c]) {
// 		constructTree(nxt, d+1);
// 	}
// }

void update(int uL, int uR, long long s, long long k, int i = 1, int cLeft = 1, int cRight = N + 1) {
	if (uL == cLeft && uR == cRight) {
		rangeTree[i].s += s + MOD;
		rangeTree[i].k += k + MOD;
		rangeTree[i].s = rangeTree[i].s % MOD;
		rangeTree[i].k = rangeTree[i].k % MOD;
		return;
	}

	int mid = (cLeft + cRight) / 2;
	if (uL < mid) update(uL, min(uR, mid), s, k, i * 2, cLeft, mid);
	if (uR > mid) update(max(uL, mid), uR, s, k, i * 2 + 1, mid, cRight);
}


long long query(int v, long long s = 0, long long k = 0, int i = 1, int cLeft = 1, int cRight = N + 1) {
	if (cRight - cLeft == 1) {
		return (((rangeTree[i].s + s + MOD) %MOD) - ((depth[v]*((k + rangeTree[i].k + MOD)%MOD)) + MOD)%MOD + MOD) % MOD;
	}
	int mid = (cLeft + cRight)/2;
	long long ans = 0;
	if (v < mid) ans += query(v, (rangeTree[i].s + s + MOD)%MOD, (rangeTree[i].k + k + MOD) % MOD, i * 2, cLeft, mid);
	else ans += query(v, (rangeTree[i].s + s + MOD)%MOD, (rangeTree[i].k + k + MOD)%MOD, i * 2 + 1,  mid, cRight);
	return ans;
}

int main(int argc, char* argv[]) {
	scanf("%d", &N);
	init();
	for (int i = 2; i <= N; i++) {
		int p;
		scanf("%d", &p);
		edges[p].push_back(i);
	}
	// constructTree(1, 0);
	compute_tree_ranges(1, 0);
	scanf("%d", &Q);
	for (int i = 0; i < Q; i++) {
		int type;
		scanf("%d", &type);
		if (type == 1) {
			int v;
			long long x,k;
			scanf("%d %lld %lld", &v, &x, &k);

			// Do some update here
			update(startRange[v], endRange[v], x + ((k*depth[indexInRangeTree[v]] + MOD) % MOD), k);
		} else {
			int v;
			scanf("%d", &v);

			// Do some query here
			long long result = query(indexInRangeTree[v]);
			printf("%lld\n", result);
		}
	}

	return 0;
}