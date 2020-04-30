#include <iostream>
#include <cstring>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <set>
#include <queue>
#include <map>
#include <utility>


#define MAXV 255
#define MAXE 66000

using namespace std;

int start[MAXV];
int succ[MAXE], to[MAXE];
int source, sink;
int cap[MAXE];
int lvl[MAXV];
int nextchld[MAXV];
int edge_counter;
int n;

int inv(int e) {
	return e ^ 1;
}

void add_edge(int u, int v, long long c) {
	origCap[edge_counter] = c, to[edge_counter] = v;
	cap[edge_counter] = c;

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

	scanf("%d", &n);
	source = n;
	sink = n + 1;
	for (int i = 0; i < n; i++) {
		int num;
		scanf("%d", &num);
		add_edge(source, i, num);
		add_edge(i, source, 0);
	}

	for (int i = 0; i < n; i++) {
		int num;
		scanf("%d", &num);
		add_edge(i, sink);
		add_edge(sink, i, 0);
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int num;
			scanf("%d", &num);
			add_edge(i, j, num);
			add_edge(j, i, 0);
		}
	}

	printf("%d\n", mf());
	return 0;
}