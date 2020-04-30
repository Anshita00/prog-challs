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

#define MAXV 100005

using namespace std;

int v, q;
int parent[MAXV];
int subtree_size[MAXV];
vector<pair<int, int> > inserted;

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
		inserted.push_back(make_pair(-1, -1));
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
}

int main() {

	scanf("%d %d", &v, &q);
	init();

	for (int i = 0; i < q; i++) {
		char t;
		scanf(" %c",&t);

		if (t == 'A') {
			int a,b;
			scanf("%d %d", &a, &b);
			a--;
			b--;
			join(a,b);
		} else if (t == 'D') {
			del();
		} else if (t == 'Q') {
			int a,b;
			scanf("%d %d", &a, &b);
			a--;
			b--;
			a = root(a);
			b = root(b);
			if (a == b) printf("1\n");
			else printf("0\n");
		}
	}

	return 0;
}