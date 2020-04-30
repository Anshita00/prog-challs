#include <iostream>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <set>
#include <queue>
#include<map>
#include <utility>

#define MAXN 100005
#define MOD 1000000007

using namespace std;
int n;
long long w[MAXN];
long long b[MAXN];
vector<int> edges[MAXN];
vector<int> children[MAXN];
vector<int> colours;
bool seen[MAXN];


void constructTree(int c) {

	for (int nxt: edges[c]) {
		if (seen[nxt]) continue;
		seen[c] = true;
		constructTree(nxt);
		children[c].push_back(nxt);
	}
}

void calculate(int u) {

	if (colours.at(u) == 0) {
		w[u] = 1;
		b[u] = 0;
	} else {
		w[u] = 0;
		b[u] = 1;
	}

	for (int v: children[u]) {
		calculate(v);

		long long tw = 0, tb = 0;
		tw = (tw + ((w[u] * w[v]) % MOD) + MOD) % MOD;
		tb = (tb + ((b[u] * w[v]) % MOD) + ((b[v] * w[u]) % MOD) + MOD) % MOD;

		tw = (tw +  ((w[u] * b[v]) % MOD) + MOD) % MOD;
		tb = (tb + ((b[u] * b[v]) % MOD) + MOD) % MOD;

		w[u] = tw;
		b[u] = tb;
	}
}

int main() {

	scanf("%d", &n);

	for (int i = 0; i < n -1; i++) {
		int p;
		scanf("%d", &p);
		edges[i+1].push_back(p);
		edges[p].push_back(i+1);
	}

	for (int i = 0; i < n; i++) {
		int p;
		scanf("%d",&p);
		colours.push_back(p);
	}

	constructTree(0);
	calculate(0);


	printf("%lld\n", b[0]);

	return 0;
}