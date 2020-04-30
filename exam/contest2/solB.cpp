#include <iostream>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <set>
#include <queue>
#include<map>
#include <utility>

using namespace std;

#define V 1102
#define W 500
#define N 100
#define E 1000500
#define INF 10005000000

int n,s,t;
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

	scanf("%d", &n);
	fill(start, start + V, -1);
	edge_counter = 0;

	s = 11*N;
	t = 11*N + 1;

	for (int i = 0; i < n; i++) {
		long long p,c;
		scanf("%lld %lld", &p, &c);
		add_edge(s, i, p);
		add_edge(i, s, 0);
		add_edge(i, t, c);
		add_edge(t, i, 0);
	}

	int w;
	scanf("%d", &w);

	for (int i = 0; i < w; i++) {
		long long l;
		int ni;
		scanf("%lld %d", &l, &ni);
		add_edge(i + N, i + N + W, l);
		add_edge(i + N + W, i + N, 0);
		for (int j = 0; j < ni; j++) {
			int c;
			scanf(" %d", &c);
			c--;
			add_edge(c, i + N, 1000001);
			add_edge(i + N, c, 0);
			add_edge(i + N + W, c, 1000001);
			add_edge(c, i + N + W, 0);
		}
	}


	printf("%lld\n", mf());

	return EXIT_SUCCESS;
}