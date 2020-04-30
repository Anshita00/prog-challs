#include <iostream>
#include<cstring>
#include <sstream>
#include <queue>

#define N 100001
#define MAXN 600001
#define INF 10000000005

using namespace std;

long long seg1[MAXN], seg2[MAXN];
long long dist[MAXN];
bool seen[MAXN];
long long n;
long long value;

typedef pair<long long, long long> edge;
vector<edge> graph[MAXN];
priority_queue<edge, vector<edge>, greater<edge>> pq;

void initFirst(long long l = 1, long long r = n + 1, long long i = 1) {
	seg1[i] = value;
	value++;

	if (r - l == 1) {
		graph[seg1[i]].push_back(make_pair(0, l));
		return;
	}

	long long mid = (l + r)/2;
	initFirst(l, min(mid,r), i * 2);
	initFirst(max(l,mid),r, i * 2 +1);
	graph[seg1[i]].push_back(make_pair(0, seg1[i*2]));
	graph[seg1[i]].push_back(make_pair(0, seg1[i*2+1]));
}

void initSecond(long long l = 1, long long r = n + 1, long long i = 1) {
	seg2[i] = value;
	value++;

	if (r - l == 1) {
		graph[l].push_back(make_pair(0, seg2[i]));
		return;
	}

	long long mid = (l + r)/2;
	initSecond(l, min(mid,r), i * 2);
	initSecond(max(l,mid),r, i * 2 +1);
	graph[seg2[i*2]].push_back(make_pair(0, seg2[i]));
	graph[seg2[i*2 + 1]].push_back(make_pair(0, seg2[i]));
}

void update(long long uL, long long uR, long long v, long long weight, int type, long long i = 1, long long cLeft = 1, long long cRight = n +1) {

	if (uL == cLeft && uR == cRight) {
		if (type == 1) {
			graph[v].push_back(make_pair(weight, seg1[i]));
		} else {
			graph[seg2[i]].push_back(make_pair(weight, v));
		}
		return;
	}

	long long mid = (cLeft + cRight)/2;
	if (uL < mid) update(uL, min(uR, mid), v, weight, type, i * 2, cLeft, mid);
	if (uR > mid) update(max(uL, mid), uR, v, weight, type, i * 2 + 1, mid, cRight);
}

void djikstra(long long s) {
	pq.push(make_pair(0, s));
	while (!pq.empty()) {
		edge cur = pq.top();
		pq.pop();
		long long v = cur.second, d = cur.first;

		if (seen[v]) continue;
		dist[v] = d;
		seen[v] = true;

		for (int i = 0; i < graph[v].size(); i++) {
			edge next = graph[v][i];
			long long u = next.second, weight = next.first;
			if (!seen[u]) pq.push(make_pair(d + weight, u));
		}
	}
}

int main() {
	long long q,s;
	scanf("%lld %lld %lld", &n, &q, &s);
	value = n + 1;

	initFirst();
	initSecond();

	for (int i = 0; i < q; i++) {
		int t;
		long long u, v, l, r, w;
		scanf("%d", &t);
		if (t == 1) {
			scanf("%lld %lld %lld", &v, &u, &w);
			update(u, u + 1, v, w, 1);
		} else {
			scanf("%lld %lld %lld %lld", &v, &l, &r, &w);
			if (t == 2) {
				update(l, r + 1, v, w, 1);
			} else if (t == 3) {
				update(l, r + 1, v, w, 2);
			}
		}
	}

	for (int i = 0; i <= value; i++) {
		seen[i] = false;
		dist[i] = INF;
	}

	djikstra(s);
	for (int i = 1; i <= n; i++) {
		if (dist[i] == INF) printf("-1 ");
		else
			printf("%lld ",dist[i]);
	}
	printf("\n");
}