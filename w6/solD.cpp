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

#define MAXV 800
#define INF 2000000000
#define MAXE 40000

using namespace std;

int n,m;
int start[MAXV];
int succ[MAXE], to[MAXE];
int source, sink;
int cap[MAXE];
int origCap[MAXE];
int lvl[MAXV];
int nextchld[MAXV];
int edge_counter;
bool seen[MAXV];

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

void dfs1(int u) {
	if (seen[u]) return;
	seen[u] = true;

	for (int e = start[u]; ~e; e = succ[e]) {
		if (cap[e] > 0) {
			dfs1(to[e]);
		}
	}
}

void dfs2(int u) {
	if (seen[u]) return;
	seen[u] = true;

	for (int e = start[u]; ~e; e = succ[e]) {
		if (cap[inv(e)] > 0) {
			dfs2(to[e]);
		}
	}
}

int main() {

	FILE *fp = fopen("attack.in", "r");
	FILE *op = fopen("attack.out", "w");
  	if (fp == NULL || op == NULL){
      perror("Error while opening the file.\n");
      exit(EXIT_FAILURE);
   	}

	int a,b;
	fscanf(fp, "%d %d %d %d", &n, &m, &a, &b);
	a--;
	b--;
	source = a;
	sink = b;
	edge_counter = 0;
	fill(start, start + MAXV, -1);

	for (int i = 0; i < m; i++) {
		int a,b,c;
		fscanf(fp, "%d %d %d", &a, &b, &c);
		a--;
		b--;
		add_edge(a,b,c);
		add_edge(b,a,c);
	}

	int maxFlow = mf();
	dfs1(source);
	dfs2(sink);

	for (int i = 0; i < n; i++) {
		if (seen[i] == 0) {
			fprintf(op, "AMBIGUOUS\n");
			return 0;
		}
	}

	fprintf(op,"UNIQUE\n");
	return 0;
}