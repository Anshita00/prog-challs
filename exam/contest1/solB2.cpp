#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <queue>
#include <stack>
#include <set>

using namespace std;

#define MAXV 100000
#define MAXN 200000
#define MAXM 100000


set<int> kingdomsSet;

typedef pair<long long, int> edge;

vector<edge> edges[MAXN];

long long dist[MAXN];
bool seen[MAXN];

void add(int u, int v, long long c) {
	edges[u].push_back(make_pair(c, v));
	if (v != u) {
		edges[v].push_back(make_pair(c, u));
	}
}

priority_queue<edge, vector<edge>, greater<edge>> pq;

void djikstra() {
	pq.push(edge(0, 0));

	while (!pq.empty()) {
		edge cur = pq.top();
		pq.pop();
		int v = cur.second;
		long long d = cur.first;

		if (seen[v]) continue;

		dist[v] = d;
		seen[v] = true;

		for (int i = 0; i < edges[v].size(); i++) {
			edge next = edges[v][i];
			int u = next.second;
			long long weight = next.first;
			if (!seen[u]) {
				pq.push(edge(d + weight, u));
			}
		}
	}
}


int main(int argc, char*argv[]) {

	int n,m;
	scanf("%d %d", &n, &m);
	int kingdoms[MAXN];
	long long cities[MAXN];
	pair<int, int> roads[MAXM];
	for (int i = 0; i < n; i++) {
		int k;
		scanf("%d", &k);
		kingdoms[i] = k;
		kingdomsSet.insert(k);
	}

	for (int i = 0; i < n; i++) {
		long long c;
		scanf("%lld", &c);
		cities[i] = c;
	}

	for (int i = 0; i < m; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		u--;
		v--;
		roads[i] = make_pair(u, v);
	//	edges[u + MAXV].push_back(edge(0, v));
	//	edges[v].push_back(edge(0, u + MAXV));
	}



	for (int k: kingdomsSet) {

		fill(dist, dist + MAXN, -1);
		fill(seen, seen + MAXN, false);

		for (int i = 0; i < n; i++) {
			edges[i].clear();
		}

		edges[0].push_back(edge(0, MAXV));

		for (int i = 0; i < m; i++) {
			pair<int, int> road = roads[i];
			int u = get<0>(road);
			int v = get<1>(road);
			edges[u + MAXV].push_back(edge(0, v));
			edges[v].push_back(edge(0, u + MAXV));
		}

		for (int i = 1; i < n; i++) {
			if (kingdoms[i] == k) {
				edges[i].push_back(edge(0, i + MAXV));
			} else {
				edges[i].push_back(edge(cities[i], i + MAXV));
			}
		}

		djikstra();
		printf("%lld\n", dist[n-1 + MAXV]);
	}

}