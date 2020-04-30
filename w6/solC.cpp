#include <iostream>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <set>
#include <queue>
#include <map>
#include <utility>

#define MAXV 50
#define INF 10000000
#define MAXE 1000
#define MAXX 1000005

using namespace std;

int n,m,x;
int start[MAXV];
int succ[MAXE], to[MAXE];
int cap[MAXE];
int origCap[MAXE];
int source, sink;
int lvl[MAXV];
int nextchld[MAXV];
int edge_counter;

int inv(int e) {
	return e ^ 1;
}

void add_edge(int u, int v, long long c) {
	origCap[edge_counter] = c, to[edge_counter] = v;

	succ[edge_counter] = start[u];
	start[u] = edge_counter;
	++edge_counter;
}

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

int aug(int u, int cflow) {
	if (u == sink) return cflow; // base case

	for (int &i = nextchld[u]; i >= 0; i = succ[i]) {
		if (cap[i] > 0) {
			int nxt = to[i];
			if (lvl[nxt] != lvl[u] + 1) continue;
			int rf = aug(nxt, min(cflow, cap[i]));
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

int mf() {
	int tot = 0;
	while (bfs()) {
		for (int x = aug(source, INF); x; x = aug(source, INF))  tot+=x;
	}
	return tot;
}


int main() {

	scanf("%d %d %d", &n, &m, &x);
	source = 0;
	sink = n - 1;
	edge_counter = 0;
	fill(start, start + MAXV, -1);
	for (int i = 0; i < m; i++) {
		int a,b, c;
		scanf("%d %d %d", &a, &b, &c);
		a--;
		b--;
		add_edge(a, b, c);
		add_edge(b, a, 0);
	}

	double lo = 0;
	double hi = MAXX;
	for (int it = 0; it < 70; it++) {
		double mid = (lo + hi) / 2;
		for (int i = 0; i < edge_counter; i++) {
			if (i % 2 == 0) {
				double c = origCap[i] / mid > x ? x : origCap[i] / mid;
				cap[i] = c;
			} else {
				cap[i] = 0;
			}
		}

		if (mf() >= x) {
			lo = mid;
		} else {
			hi = mid;
		}
	}

	printf("%0.10lf\n", lo * x);

	return 0;
}