#include <iostream>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <set>
#include <queue>
#include <map>
#include <utility>

using namespace std;

#define V 102
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

	map<pair<int, int>, long long> edges;
	scanf("%d", &n);
	fill(start, start + V, -1);
	edge_counter = 0;

	s = N;
	t = N + 1;
	vector<int> prevCities;

	for (int i = 0; i < n; i++) {
		long long p,c;
		scanf("%lld %lld", &p, &c);
		// if (p != 0) {
			add_edge(s, i, p);
			add_edge(i, s, 0);
		// }
		// if (c != 0) {
			add_edge(i, t, c);
			add_edge(t, i, 0);
		// }
	}

	int w;
	scanf("%d", &w);

	for (int i = 0; i < w; i++) {
		long long l;
		int ni;
		prevCities.clear();
		scanf("%lld %d", &l, &ni);
		for (int i = 0; i < ni; i++) {
			int c;
			scanf(" %d", &c);
			c--;
			for (auto it = prevCities.begin(); it != prevCities.end(); it++) {
				int curCity = *it;
				if (curCity < c) swap(c, curCity);
				pair<int, int> cityPair = make_pair(c, curCity);
				if (edges.find(cityPair) != edges.end()) {
					long long temp = edges[cityPair];
					edges[cityPair] = temp + l;
				} else {
					edges[cityPair] = l;
				}
				// add_edge(c, curCity, l);
				// add_edge(curCity, c, 0);
				// add_edge(curCity, c, l);
				// add_edge(c, curCity, 0);
			}
			prevCities.push_back(c);
		}
	}

	for (auto it = edges.begin(); it != edges.end(); it++) {
		pair<int, int> cityPair = it->first;
		long long totalWeight = it->second;
		int c1 = get<0>(cityPair);
		int c2 = get<1>(cityPair);
		add_edge(c1, c2, totalWeight);
		//add_edge(c1, c2, 0);
		add_edge(c2, c1, totalWeight);
		//add_edge(c2, c1, 0);
	}

	for (int i = 0; i < edge_counter; i++) {
		printf("Edge is from %d to %d with capacity %lld\n", to[inv(i)], to[i], cap[i]);
	}

	// printf("%lld\n", mf());

	return EXIT_SUCCESS;
}