#include <iostream>
#include <cstring>
#include <vector>
#include <sstream>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <cmath>

using namespace std;

const float MAXVAL = 10001;
int parent[500];
int subtree_size[500];

struct edge {
	int u, v;
	float w;
};

bool operator< (const edge& a, const edge& b) {
	return a.w < b.w;
}

bool operator> (const edge& a, const edge& b) {
	return a.w > b.w;
}

void init(int n) {
	for (int i = 0; i < n; i++) {
		parent[i] = i;
		subtree_size[i] = 1;
	}
}

int root(int x) {
	return parent[x] == x ? x : parent[x] = root(parent[x]);
}

void join(int x, int y) {
	x = root(x); y = root(y);

	if (x == y) return;
	if (subtree_size[x] < subtree_size[y]) {
		parent[x] = y;
		subtree_size[y] += subtree_size[x];
	} else {
		parent[y] = x;
		subtree_size[x] += subtree_size[y];
	}
}

int main() {
	int T;
	scanf("%d", &T);

	while (T--) {
		int S, P;
		vector<pair<int, int>> coords;
		scanf("%d %d", &S, &P);
		vector<edge> edges;
		init(P);

		for (int i = 0; i < P; i++) {
			int x;
			int y;
			scanf("%d %d", &x, &y);
			coords.push_back(make_pair(x,y));
		}

		for (int i = 0; i < P; i++) {
			for (int j = i + 1; j < P; j++) {
				pair<int, int> firstCoord = coords.at(i);
				pair<int, int> secondCoord = coords.at(j);
				int x2 = secondCoord.first;
				int x1 = firstCoord.first;
				int y2 = secondCoord.second;
				int y1 = firstCoord.second;
				float distance = sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
				edge e;
				e.u = i;
				e.v = j;
				e.w = distance;
				edges.push_back(e);
			}
		}

		sort(edges.begin(), edges.end());
		priority_queue <edge, vector <edge>> maxEdges;
		set<int> vertices;
		int count = 0;
		for (auto it = edges.begin(); it != edges.end(); it++) {
			edge& e = *it;
			if (root(e.u) != root(e.v)) {
				maxEdges.push(e);
				join(e.u, e.v);
				count++;
			}
			if (count == P -S) {
				printf("%.2f\n", e.w);
				break;
			}
		}

	}

}