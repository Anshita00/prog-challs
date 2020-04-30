#include <iostream>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <set>
#include <queue>
#include <map>
#include <utility>

using namespace std;

#define MAXL 8005
#define MAXG 805
#define MAXC 1000000000
#define INF 64000000000000000

int l, g;
unsigned long long s[MAXL+1];
unsigned long long dp[MAXG+1][MAXL+1];

unsigned long long Cost(int i, int j) {
	return (s[j]-s[i])*(j-i);
}

void dnc(int qL, int qR, int cL, int cR, int k) {
	if (cR <= cL) return;
	int bestpos(-1);
	int mid = (cL + cR) / 2;
	dp[k][mid] = INF;
	for (int i = qL; i <= min(qR, mid - 1); i++) {
		unsigned long long newcost = dp[k-1][i] + Cost(i, mid);
		if (newcost < dp[k][mid]) {
			dp[k][mid] = newcost;
			bestpos = i;
		}
	}

	dnc(qL, bestpos, cL, mid, k);
	dnc(bestpos, qR, mid + 1, cR, k);
}

int main() {

	scanf("%d %d", &l, &g);

	for (int i = 1; i <= l; i++) {
		unsigned long long c;
		scanf("%llu", &c);
		s[i] = s[i-1] + c;
	}

	for (int j = 1; j <= l; j++) {
		dp[0][j] = INF;
	}

	for (int j = 1; j <= g; j++) dnc(0, l, 1, l + 1, j);
	printf("%llu\n", dp[g][l]);
	return 0;
}