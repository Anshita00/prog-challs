#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;

#define MAXV 300000
#define MAXN 600000
#define MAXM 1200000

int n,m;
typedef pair<long long, int> edge;

vector<edge> edges[MAXM];

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

int main(int argc, char* argv[]) {

	fill(dist, dist + MAXN, -1);
	fill(seen, seen + MAXN, false);

	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		long long d;
		scanf("%lld", &d);
		edges[i].push_back(make_pair(d, i + MAXV));
		edges[i + MAXV].push_back(make_pair(0, i));
	}

	for (int i = 0; i < m; i++) {
		int a, b;
		long long c;
		scanf("%d %d %lld", &a, &b, &c);
		a--;
		b--;
		if (c == 0) {
			a = a + MAXV;
			b = b + MAXV;
		}
		add(a, b, c);
	}

	djikstra();
	printf("%lld\n", dist[n-1]);

	return 0;
}