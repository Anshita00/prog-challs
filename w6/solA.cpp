#include <iostream>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <set>
#include <queue>
#include <map>
#include <utility>

#define MAXN 500
#define INF 100000000
#define MAXV 1003
#define MAXE 3000000

using namespace std;

int n,m,k;
int start[MAXV];
int succ[MAXE], to[MAXE];
long long cap[MAXE];
int source, potions, sink;
long long lvl[MAXV];
int nextchld[MAXV];
int edge_counter;
// bool seen[MAXV];

int inv(int e) {
	return e ^ 1;
}

void add_edge(int u, int v, long long c) {
	cap[edge_counter] = c, to[edge_counter] = v;

	succ[edge_counter] = start[u];
	start[u] = edge_counter;
	++edge_counter;
}

// bool augment(int u, int t, int f) {
// 	if (u == t) return true;
// 	if (seen[u]) return false;
// 	seen[u] = true;

// 	for (int e = start[u]; ~e; e =succ[e]) {
// 		if (cap[e] >= f && augment(to[e], t, f)) {
// 			cap[e] -= f;
// 			cap[inv(e)] += f;
// 			return true;
// 		}
// 	}

// 	return false;
// }

// int max_flow(int s, int t) {
// 	int res = 0;
// 	fill(seen, seen + MAXV, false);
// 	while(augment(s, t, 1)) {
// 		fill(seen, seen + MAXV, false);
// 		res += 1;
// 	}
// 	return res;
// }

bool bfs() {
	for (int i = 0; i < MAXV; i++) lvl[i] = -1;
	queue<int> q;
	q.push(source);
	lvl[source] = 0;

	while (!q.empty()) {
		int u = q.front();
		q.pop();
		nextchld[u] = start[u];
		for (int e = start[u]; ~e; e = succ[e]) {
			if (cap[e] > 0) {
				int nxt = to[e];
				if (lvl[nxt] != -1) continue;
				lvl[nxt] = lvl[u] + 1;
				q.push(nxt);
			}
		}
	}

	return lvl[sink] != -1;
}

long long aug(int u, long long cflow) {
	if (u == sink) return cflow; // base case

	for (int &i = nextchld[u]; i >= 0; i = succ[i]) {
		if (cap[i] > 0) {
			int nxt = to[i];
			if (lvl[nxt] != lvl[u] + 1) continue;
			long long rf = aug(nxt, min(cflow, cap[i]));
			if (rf > 0) {
				cap[i] -= rf;
				cap[i^1] += rf;
				return rf;
			}
		}r
	}
	lvl[u] = -1;
	return 0;
}

long long mf() {
	long long tot = 0;
	while (bfs()) {
		for (long long x = aug(source, INF); x; x = aug(source, INF))  tot+=x;
	}
	return tot;
}


int main() {

	fill(start, start + MAXV, -1);
	edge_counter = 0;

	scanf("%d %d %d", &n, &m, &k);
	source = (n + m);
	sink = (n + m) + 1;
	potions = (n + m) + 2;

	add_edge(source, potions, k);
	add_edge(potions, source, 0);

	for (int i = 0; i < n; i++) {
		int num;
		scanf("%d", &num);
		add_edge(source, i, 1);
		add_edge(i, source, 0);

		add_edge(potions, i, 1);
		add_edge(i, potions, 0);

		for (int j = 0; j < num; j++) {
			int t;
			scanf("%d", &t);
			add_edge(i, t - 1 + n, 1);
			add_edge(t - 1 + n, i, 0);
		}
	}

	for (int i = 0; i < m; i++) {
		add_edge(i + n, sink, 1);
		add_edge(sink, i + n, 0);
	}

	// for (int i = 0; i < edge_counter; i++) {
	// 	printf("Edge is from %d to %d with capacity %lld\n", to[inv(i)], to[i], cap[i]);
	// }

	printf("%lld\n", mf());
}