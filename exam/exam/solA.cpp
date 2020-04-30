#include <iostream>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <set>
#include <queue>
#include<map>
#include <utility>

using namespace std;

#define N 1000
#define M 1000
#define V 2002
#define E 10000000
#define INF 1000500000

int s,t;
int start[V];
int succ[E], to[E];
long long cap[E];
int lvl[V];
int nextchld[V];
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


bool bfs() {
	for (int i = 0; i < V; i++) lvl[i] = -1;
	queue<int> q;
	q.push(s);
	lvl[s] = 0;

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

	return lvl[t] != -1;
}

long long aug(int u, long long cflow) {
	if (u == t) return cflow; // base case

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
		}
	}
	lvl[u] = -1;
	return 0;
}

long long mf() {
	long long tot = 0;
	while (bfs()) {
		for (long long x = aug(s, INF); x; x = aug(s, INF))  tot+=x;
	}
	return tot;
}


int main(int argc, char* argv[]) {

	int n,m;
	scanf("%d %d", &n, &m);

	edge_counter = 0;
	fill(start, start + V, -1);

	s = N + M;
	t = N + M + 1;

	for (int i = 0; i < n; i++) {
		long long c;
		scanf("%lld", &c);
		add_edge(s, i, c);
		add_edge(i, s, 0);
	}

	for (int i = 0; i < m; i++) {
		long long c;
		scanf("%lld", &c);
		add_edge(i + N, t, c);
		add_edge(t, i + N, 0);
	}

	for (int i = 0; i < n; i++) {
		int k;
		scanf("%d", &k);
		for (int j = 0; j < k; j++) {
			int v;
			scanf("%d", &v);
			v--;
			add_edge(i, v + N, 1);
			add_edge(v + N, i, 0);
		}
	}

	// for (int i = 0; i < edge_counter; i++) {
	// 	printf("Edge is from %d to %d with capacity %lld\n", to[inv(i)], to[i], cap[i]);
	// }

	printf("%lld\n", mf());

	return 0;
}