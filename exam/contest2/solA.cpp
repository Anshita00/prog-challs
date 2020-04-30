#include <iostream>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <set>
#include <queue>
#include<map>
#include <utility>

using namespace std;

#define MAXN 1001
#define MAXB 1001
#define MAXF 1000
#define MOD 1000000007

int main(int argc, char* argv[]) {

	int n,b,f;
	long long dp[MAXN][MAXB];
	int costs[MAXN];

	scanf("%d %d %d", &n, &b, &f);

	for (int i = 1; i <= n; i++) {
		int d;
		scanf("%d", &d);
		costs[i] = d;
	}

	for (int i = 0; i <= b; i++) {
		dp[0][i] = 1;
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= b; j++) {
			dp[i][j] = dp[i-1][j];
			if (costs[i] <= j) {
				dp[i][j] = (((dp[i][j] + dp[i-1][j-costs[i]])%MOD) + MOD) % MOD;
			}
		}
	}

	printf("%lld\n", dp[n][b]);

	return 0;
}