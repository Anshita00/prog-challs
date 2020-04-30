#include <iostream>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <set>
#include <queue>
#include <map>
#include <utility>

using namespace std;

#define MAXV 360002
#define N 600
#define MAXE 1464100
#define INF 10000000

int n;
int start[MAXV];
int succ[MAXE], to[MAXE];
int cap[MAXE];
int source, sink;
int lvl[MAXV];
int nextchld[MAXV];
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

	int k;
	scanf("%d", &k);
	char grid[N][N];
	int which[N][N];

	for (int temp = 1; temp <=k; temp ++) {
		edge_counter = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				grid[i][j] = 0;
			}
		}


		fill(start, start + MAXV, -1);
		fill(succ, succ + MAXE, 0);
		fill(cap, cap + MAXE, 0);
		fill(to, to + MAXE, 0);
		fill(lvl, lvl + MAXV, 0);
		fill(nextchld, nextchld + MAXV, 0);

		scanf("%d", &n);
		source = n*n;
		sink = n*n + 1;
		int cur = 0;
		for (int i = 0; i < n; i++) {
			if (i > 0) {
				cur = (which[i-1][0] + 1)%2;
			}
			for (int j = 0; j < n; j++) {
				char c;
				scanf(" %c", &c);
				grid[i][j] = c;
				which[i][j] = cur;
				cur = (cur + 1)%2;
			}

		}

		// for (int i = 0; i < n; i++) {
		// 	for (int j = 0; j < n; j++) {
		// 		printf("%d", which[i][j]);
		// 	}
		// 	printf("\n");
		// }

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (which[i][j] == 0) {
					add_edge(source, i * n + j, 1);
					add_edge(i * n + j, source, 0);
				} else {
					add_edge(i * n + j, sink, 1);
					add_edge(sink, i * n + j, 0);
				}
				if (grid[i][j] == '#' && which[i][j] == 0) {
					if (i != 0 && grid[i-1][j] == '#') {
						add_edge(i*n + j, (i-1)*n + j, 1);
						add_edge((i-1)*n + j, i*n + j, 0);
					}
					if (j != 0 && grid[i][j-1] == '#') {
						add_edge(i*n + j, i*n + j - 1, 1);
						add_edge(i*n + j - 1, i*n + j, 0);
					}
					if (j != n - 1 && grid[i][j+1] == '#') {
						add_edge(i*n + j, i*n + j + 1, 1);
						add_edge(i*n + j + 1, i*n + j, 0);
					}
					if (i != n - 1 && grid[i+1][j] == '#') {
						add_edge(i*n + j, (i+1)*n + j, 1);
						add_edge((i+1)*n + j, i*n + j, 0);
					}
				}
			}
		}

		// for (int i = 0; i < edge_counter; i++) {
		// 	printf("Edge no. %d", i);
		// 	printf("Capcity is - %d,", cap[i]);
		// 	printf("To - %d, ", to[i]);
		// 	printf("From - %d\n", to[inv(i)]);
		// }

		printf("Case %d: %d\n", temp, mf());

	}

	return 0;
}