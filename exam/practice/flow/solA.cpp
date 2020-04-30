#include <iostream>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <set>
#include <queue>
#include<map>
#include <utility>

using namespace std;

#define V 50
#define E 500
#define INF 4000000000

int n,s,t;
int start[V];
int succ[E], to[E];
long long cap[E];
int lvl[V];
int nextchld[V];
int edge_counter;
bool seen[V];

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

void check_reach(int u) {
	if (seen[u]) return;
	seen[u] = true;
	for (int e = start[u]; ~e; e = succ[e]) {
		if (cap[e] > 0) check_reach(to[e]);
	}
}

vector<int> min_cut() {
	long long total_size = mf();
	vector<int> ans;
	fill(seen, seen + V, 0);
	check_reach(s);

	for (int e = 0; e < edge_counter; e += 2) {
		if (!seen[to[e]] && seen[to[inv(e)]]) {
			ans.push_back(e);
		}
	}

	return ans;
}

int main(int argc, char* argv[]) {

	int m;
	while (true) {
		scanf("%d %d", &n, &m);
		edge_counter = 0;
		fill(start, start + V, -1);
		fill(cap, cap + E, 0);
		fill(to, to + E, 0);
		fill(succ, succ + E, 0);
		s = 0;
		t = 1;
		if (n == 0 && m == 0) break;
		for (int i = 0; i < m; i++) {
			int u,v;
			long long c;
			scanf("%d %d %lld", &u, &v, &c);
			u--;
			v--;
			add_edge(u,v,c);
			add_edge(v, u, 0);
			add_edge(v, u, c);
			add_edge(u, v, 0);
		}


		vector<int> result = min_cut();
		for (int edge : result) {
			printf("%d %d\n", to[inv(edge)] + 1, to[edge] + 1);
		}
		printf("\n");
	}

	return 0;
}