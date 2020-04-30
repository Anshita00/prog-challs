#include <iostream>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <set>
#include <queue>
#include<map>
#include <utility>

#define MAXN 100

int N, M;
int E = 8*N^2;
int start[2*N];
int succ[E], to[E];
long long cap[E];
int edge_counter;

int inv(int e) {
	return e ^ 1;
}

void add_edge(int u, int v, long long c) {
	cap[edge_counter] c, to[edge_counter] = v;

	succ[edge_counter] = start[u];
	start[u] = edge_counter;
	++edge_counter;
}

int main() {

	scanf("%d", &N);
	fill(start, start + 2*N, -1);
	edge_counter = 0;

	for (int i = 0; i < n; i++) {
		long long cap;
		scanf("%lld", &cap);
		add_edge(i, i + N, cap);
		add_edge(i + N, i, cap);
	}


	return 0;
}