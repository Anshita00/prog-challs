#include <iostream>
#include<cstring>
#include <sstream>
#include <queue> 

using namespace std;
int dist[100];

const int INF = -2147483647 - 1;

struct edge {
	int u;
	int v;
	int w;

	bool operator> (const edge &e) const {
		return this->w > e.w;
	}

	bool operator< (const edge &e) const {
		return this->w < e.w;
	}
};
vector<edge> edges;
vector<int> bfsEdges[100];

bool relax() {
	bool relaxed = false;
	for (auto e = edges.begin(); e != edges.end(); e++) {
		if (dist[e->u] != INF && dist[e->v] < dist[e->u] + e->w && dist[e->u] + e->w > 0) {
			relaxed = true;
			dist[e->v] = dist[e->u] + e->w;
		}
	}
	return relaxed;
}

bool bfs(int start, int n) {
	int dist[100];
	int prev[100];

	fill(dist, dist + 100, -1);
	dist[start] = 0;
	prev[start] = -1;

	queue<int> q;
	q.push(start);
	while (!q.empty()) {
		int c = q.front();
		q.pop();
		for (int nxt : bfsEdges[c]) {
			if (dist[nxt] == -1) {
				dist[nxt] = dist[c] + 1;
				prev[nxt] = c;
				q.push(nxt);
			}
		}
	}

	if (dist[n-1] >= 0) {
		return true;
	}
	return false;
} 

void find_game_winnable(int n) {
	fill(dist, dist + 100, INF);
	dist[0] = 100;

	for (int i = 0; i < n - 1; i++) {
		if (relax() == false) {
			if (dist[n-1] > 0) {
				printf("winnable\n");
				return;
			}
			printf("hopeless\n");
			return;
		}
	}

	bool relaxed = false;
	for (auto e = edges.begin(); e != edges.end(); e++) {
		// printf("Edge is %d to %d with weight %d\n", e->u, e->v, e->w);
		if (dist[e->u] != INF && dist[e->v] < dist[e->u] + e->w && dist[e->u] + e->w > 0) {
			dist[e->v] = dist[e->u] + e->w;
			relaxed = true;
			if (bfs(e->u, n)) {
				printf("winnable\n");
				return;
			}
		}
	}

	if (relaxed == false && dist[n-1] > 0) {
		printf("winnable\n");
	} else {
		printf("hopeless\n");
	}


}

int main() {
	while (true) {
		int n;
		edges.clear();
		for (int i = 0; i < 100; i++) {
			bfsEdges[i].clear();
		}
		scanf("%d", &n);
		if (n == -1) break;
		for (int i = 0; i < n; i++) {
			int energy;
			scanf("%d", &energy);
			int numRooms;
			scanf("%d", &numRooms);
			for (int j = 0; j < numRooms; j++) {
				edge e;
				e.u = i;
				int vertex;
				scanf("%d", &vertex);
				e.v = vertex - 1;
				e.w = energy;
				edges.push_back(e);
				bfsEdges[i].push_back(vertex-1);
			}
		}

		find_game_winnable(n);
	}
}