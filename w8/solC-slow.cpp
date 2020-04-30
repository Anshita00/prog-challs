#include <iostream>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <set>
#include <queue>
#include <map>
#include <utility>

using namespace std;

#define MAXL 8000
#define MAXG 800
#define MAXC 1000000000
#define INF 100000000000000

int l, g;
long long c[MAXL+1];
long long s[MAXL+1];
long long dp[MAXG + 1][MAXL + 1];


int main() {

	scanf("%d %d", &l, &g);

	for (int i = 1; i <= l; i++) {
		scanf("%lld", &c[i]);
		s[i] = s[i-1]+c[i];
	}

	for (int j = 1; j <= l; j++) {
		dp[0][j] = INF;
	}

	for (int i = 1; i <= g; i++) {
		for (int j = 1; j <= l; j++) {
			dp[i][j] = INF;
			for (int t = 0; t < j; t++) {
				dp[i][j] = min(dp[i][j], dp[i-1][t] +  (s[j]-s[t])*(j-t));
			}
		}
	}

	printf("%lld\n", dp[g][l]);
	return 0;
}