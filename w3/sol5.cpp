#include <iostream>
#include<cstring>
#include <sstream>
#include <queue>
#include <algorithm>
 
#define N 200005
#define LOGN 19
 
using namespace std;
 
int parent[N];
int subtree_size[N];
int par[N][LOGN];
long long maxWeight[N][LOGN];
int depth[N];
int logs[N];
 
vector<pair<int, long long> > edgesAdj[N];
 
struct edge {
	int u, v;
	long long w;
 
	bool operator> (const edge &e) const {
		return this->w > e.w;
	}
 
	bool operator< (const edge &e) const {
		return this->w < e.w;
	}
};
 
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
 
void constructTree(int p, pair<int, long long> &edge) {
	int c = edge.first;
	// if (par[c][0] || depth[c]) return;
	par[c][0] = p;
	depth[c] = depth[p] + 1;
	maxWeight[c][0] = edge.second;
 
	for (pair<int, long long> &nxt: edgesAdj[c]) {
		if (nxt.first == par[c][0]) continue;
		constructTree(c, nxt);
	}
}
 
void preprocess(int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 1; (1<<j) < n; j++) {
			par[i][j] = -1;
			maxWeight[i][j] = -1;
		}
	}
 
	for (int j = 1; (1<<j) < n; j++) {
		for (int i = 0; i < n; i++) {
			if (par[i][j-1] != -1) {
				par[i][j] = par[par[i][j-1]][j-1];
				maxWeight[i][j] = max(maxWeight[i][j-1], maxWeight[par[i][j-1]][j-1]);
			}
		}
	}
 
	logs[0] = 0;
	logs[1] = 0;
 
	for (int i = 2; i <= n + 1; i++) {
		logs[i] = logs[i/2] + 1;
	}
 
}
 
 
long long findMaxEdge(int u, int v) {
 
	long long maxEdge = 0;
	if (depth[u] < depth[v]) swap(u,v);
 
	for (int i = logs[depth[u]]; i >= 0; i--) {
		if (depth[u] - (1<<i) >= depth[v]) {
			maxEdge = max(maxEdge, maxWeight[u][i]);
			u = par[u][i];
		}
	}
 
	if (u == v) return maxEdge;
 
	for (int i = logs[depth[u]]; i >= 0; i--) {
		if (par[u][i] != -1 && par[u][i] != par[v][i]) {
			maxEdge = max(maxEdge, max(maxWeight[u][i], maxWeight[v][i]));
			u = par[u][i];
			v = par[v][i];
		}
	}
 
	maxEdge = max(maxEdge, max(maxWeight[u][0], maxWeight[v][0]));
	return maxEdge;
}
 
 
int main() {
	int m,n;
	edge edgeList[N];
	edge edgeListCopy[N];
	scanf("%d %d", &n, &m);
	init(n);
 
	for (int i = 0; i < m; i++) {
		int u, v;
		long long w;
		scanf("%d %d %lld", &u, &v, &w);
		edge e1, e2;
		e1.u = u-1;
		e1.v = v-1;
		e1.w = w;
		e2.u = u-1;
		e2.v = v-1;
		e2.w = w;
		edgeList[i] = e1;
		edgeListCopy[i] = e2;
	}
 
 
	bool inMST[N];
	// for (int i = 0; i < m; i++) {
	// 	inMST[i] = false;
	// }
	sort(edgeList, edgeList + m);
	long long total_weight = 0;
 
	for (int i = 0; i < m; i++) {
		edge e = edgeList[i];
 
		if (root(e.u) != root(e.v)) {
			total_weight += e.w;
			join(e.u, e.v);
			inMST[i] = true;
		}
	}
 
	for (int i = 0; i < m; i++) {
		if (inMST[i]) {
			// printf("%d\n", i);
			edge& e = edgeList[i];
			edgesAdj[e.u].push_back(make_pair(e.v,e.w));
			edgesAdj[e.v].push_back(make_pair(e.u, e.w));
		}
	}
 
	// printf("%lld", total_weight);
	// for (int i = 0; i < m; i++) {
	// 		edge& e = edgeListCopy[i];
	// 		printf("i- %d, u- %d, v-  %d\n", i, e.u, e.v);
	// }
 
	// for (int i = 0; i < n; i++) {
	// 	for (pair<int, int> nxt: edgesAdj[i]) {
	// 		int v = nxt.first;
	// 		int w = nxt.second;
	// 		printf("V- %d, W- %d ", v, w);
	// 	}
	// 	printf("\n");
	// }
 
	// for (int i = 0; i <n; i++) {
	// 	if (inMST[i]) {
	// 		printf("In MST %d", i);
	// 	}
	// }


	par[0][0] = -1;
	depth[0] = 1;
	maxWeight[0][0] = 0;
 
	for (pair<int, long long> &nxt: edgesAdj[0]) {
		constructTree(0, nxt);
	}

	// for (int i = 0; i < n; i++) {
	// 	printf("Parent: %d\n", par[i][0]);
	// 	printf("Size: %d\n", sizeTree[i]);
	// 	printf("Depth: %d\n", depth[i]);
	// 	printf("Children: \n");
	// 	for (auto it = children[i].begin(); it != children[i].end(); it++) {
	// 		pair<int, int> current = *it;
	// 		printf("Vertex: %d, Weight: %d\n", current.first, current.second);
	// 	}
	// }
	preprocess(n);
	// for (int i = 0; i < 20; i++) {
	// 	printf("%d\n", log[i]);
	// }
 
 
	for (int i = 0; i < m; i++) {
		int u, v;
		u = edgeListCopy[i].u;
		v = edgeListCopy[i].v;
		if (par[u][0] == v || par[v][0] == u) {
			printf("%lld\n", total_weight);
		} else {
			long long maxWeight = findMaxEdge(u,v);
			// printf("Max edge is %d, total weight is %lld\n", maxWeight, total_weight);
			long long finalWeight = total_weight - maxWeight + edgeListCopy[i].w;
			printf("%lld\n", finalWeight);
		}
	}
	// for (int i = 0; i < 5; i++) {
	// 	int u, v;
	// 	scanf("%d %d", &u, &v);
	// 	u--;
	// 	v--;
	// 	int res = lca(u, v);
	// 	int maxEdgeWeight = findMaxEdge(u, v, res);
	// 	printf("%d\n", maxEdgeWeight)
 
	// 	// printf("Result node: %d\n", res);
	// 	// printf("Depth of u: %d\n", depth[u]);
	// 	// printf("Depth of v: %d\n", depth[v]);
	// 	// printf("Depth of res: %d\n", depth[res]);
	// }
 
 
 
 
}