#include <iostream>
#include <cstring>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <set>
#include <queue>
#include <map>
#include <utility>

#define MAXV 300003
#define MAXQ 300003

using namespace std;

set<pair<int, int>> edges [MAXQ<<2];
int v, q;
int parent[MAXV];
int subtree_size[MAXV];
vector<pair<int, int> > inserted;
map<pair<int, int>, int > queryForEdge;
set<int> queries;
int ans;
FILE* op;
//bool seen[266666];


void init2() {
	for (int i = 0; i < MAXV<<2; i++) {
		edges[i] = {};
	}
}

void deleteUpdate(int uL, int uR, pair<int, int> edge, int i = 1, int cLeft = 1, int cRight = q + 1){

	if (uL == cLeft && uR == cRight) {
		edges[i].erase(edge);
		return;
	}

	int mid = (cLeft + cRight) / 2;
	if (uL < mid) deleteUpdate(uL, min(uR, mid), edge, i * 2, cLeft, mid);
	if (uR > mid) deleteUpdate(max(uL, mid), uR, edge, i * 2 + 1, mid, cRight);
}

void update(int uL, int uR, pair<int, int> edge, int i = 1, int cLeft = 1, int cRight = q + 1) {
	if (uL == cLeft && uR == cRight) {
		edges[i].insert(edge);
		return;
	}

	int mid = (cLeft + cRight) / 2;
	if (uL < mid) update(uL, min(uR, mid), edge, i * 2, cLeft, mid);
	if (uR > mid) update(max(uL, mid), uR, edge, i * 2 + 1, mid, cRight);
}

// set<pair<int, int>> query(int p, set<pair<int, int>> curSet, int i = 1, int cLeft = 1, int cRight = q + 1) {
// 	if (cRight - cLeft == 1) {
// 		curSet.insert(edges[i].begin(), edges[i].end());
// 		return curSet;
// 	}

// 	int mid = (cLeft + cRight) / 2;
// 	curSet.insert(edges[i].begin(), edges[i].end());
// 	if (p < mid) return query(p,curSet, i * 2, cLeft, mid);
// 	else return query(p, curSet,i * 2 + 1, mid, cRight);
// }

void init() {
	for (int i = 0; i < v; i++) {
		parent[i] = i;
		subtree_size[i] = 1;
	}
}

int root(int x) {
	return parent[x] == x ? x : root(parent[x]);
}

void join(int x, int y) {
	x = root(x); y = root(y);
	if (x == y) {
		inserted.push_back(make_pair(-1,-1));
		return;
	}
	if (subtree_size[x] < subtree_size[y]) {
		parent[x] = y;
		subtree_size[y] += subtree_size[x];
		inserted.push_back(make_pair(x,y));
	} else {
		parent[y] = x;
		subtree_size[x] += subtree_size[y];
		inserted.push_back(make_pair(y,x));
	}
	ans--;
}

void del() {
	pair<int,int> p = inserted.back();
	inserted.pop_back();
	int x = p.first;
	int y = p.second;

	if (x == -1 && y == -1) {
		return;
	}

	parent[x] = x;
	subtree_size[y] -= subtree_size[x];
	ans++;
}

void dfs(int u = 1, int cLeft = 1, int cRight = q + 1) {
	//if (seen[u] return);
	//seen[u] = true;

	int numAdded = 0;

	for (auto it = edges[u].begin(); it != edges[u].end(); it++) {
		join(it->first, it->second);
		numAdded++;
	}

	if (cRight - cLeft == 1) {
		auto it = queries.find(cLeft);
		if (it != queries.end()) {
			fprintf(op, "%d\n",ans);
		}

		for (int i = 0; i < numAdded; i++) {
			del();
		}

		return;
	}

	int mid = (cLeft + cRight) / 2;
	dfs(u * 2, cLeft, mid);
	dfs(u * 2 + 1, mid, cRight);

	for (int i = 0; i < numAdded; i++) {
		del();
	}
}

int main() {

	FILE *fp = fopen("connect.in", "r");
	op = fopen("connect.out", "w");
  	if (fp == NULL || op == NULL){
      perror("Error while opening the file.\n");
      exit(EXIT_FAILURE);
   	}

	fscanf(fp, "%d %d", &v, &q);
	init();
	init2();

	for (int i = 1; i <= q; i++) {
		char t;
		fscanf(fp, " %c",&t);

		if (t == '+') {
			int a,b;
			fscanf(fp, "%d %d", &a, &b);
			a--;
			b--;
			if (a > b) swap(a,b);
			//edgesAtQuery.emplace(i, make_pair(a,b));
			//update(i, q + 1, make_pair(a,b));
			queryForEdge[make_pair(a,b)] = i;
			//pair<map<pair<int, int>, pair<int, int> >::iterator, bool> res = ranges.insert(make_pair(make_pair(a,b), make_pair(i,q + 1)));
			//if (res.second == false) {
			//}
		} else if (t == '-') {
			int a,b;
			fscanf(fp, "%d %d", &a, &b);
			a--;
			b--;
			if (a > b) swap(a,b);
			pair<int, int> edgeAtQuery = make_pair(a,b);
			update(queryForEdge[edgeAtQuery], i, edgeAtQuery);
			queryForEdge.erase(edgeAtQuery);
		} else if (t == '?') {
			queries.insert(i);
		}
	}

	ans = v;

	for (auto edge : queryForEdge) {
		update(edge.second, q + 1, edge.first);
	}

	dfs();

	// set<pair<int, int> > myset = query(4, {});
	// for (auto it = myset.begin(); it != myset.end(); it++) {
	// 	printf("%d %d\n", it->first, it->second);
	// }


	return 0;
}