#include <iostream>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <set>
#include <queue>
#include<map>
#include <utility>

#define MAXN 100
#define MAXE 8*100*100 + 10
#define INF 10000000000

using namespace std;

int N, M;
int start[2*MAXN+2];
int succ[MAXE], to[MAXE];
long long cap[MAXE];
int source = 2*N, sink = 2*N + 1;
long long lvl[2*MAXN+2];
int nextchld[2*MAXN+2];

int edge_counter;

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
	for (int i = 0; i < 2*MAXN + 2; i++) lvl[i] = -1;
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
		}
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

	while (scanf("%d", &N) != EOF) {
		fill(start, start + 2*N+2, -1);
		source = 2 * N;
		sink = 2 * N + 1;
		edge_counter = 0;

		for (int i = 0; i < N; i++) {
			long long cap;
			scanf("%lld", &cap);
			add_edge(i, i + N, cap);
			add_edge(i + N, i, 0);
		}

		scanf("%d", &M);
		for (int i = 0; i < M; i++) {
			int s, e;
			long long c;
			scanf("%d %d %lld", &s, &e, &c);
			s--, e--;
			add_edge(s+ N, e, c);
			add_edge(e, s + N, 0);
		}

		int B,D;
		scanf("%d %d", &B, &D);

		for (int i = 0; i < B; i++) {
			int pos;
			scanf("%d", &pos);
			pos--;
			//printf("This is from %d to %d", source, pos);
			add_edge(source, pos, INF);
			add_edge(pos, source, 0);
		}

		for (int i = 0; i < D; i++) {
			int pos;
			scanf("%d", &pos);
			pos--;
			add_edge(pos + N, sink, INF);
			add_edge(sink, pos + N, 0);
		}

		// for (int i = 0; i < edge_counter; i++) {
		// 	printf("Edge is from %d to %d with capacity %lld\n", to[inv(i)], to[i], cap[i]);
		// }

		printf("%lld\n", mf());
	}

	return 0;
}