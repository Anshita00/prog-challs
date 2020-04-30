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
	long long dp[2][MAXB][2];
	int costs[MAXN];

	scanf("%d %d %d", &n, &b, &f);

	for (int i = 1; i <= n; i++) {
		int d;
		scanf("%d", &d);
		costs[i] = d;
	}

	for (int i = 0; i <= b; i++) {
		dp[0][i][0] = 1;
		dp[0][i][1] = 0;
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= b; j++) {
			dp[i%2][j][0] = dp[(i-1)%2][j][0] + dp[(i-1)%2][j][1];
			dp[i%2][j][1] = 0;
			if (costs[i] <= j) {
				dp[i%2][j][1] = (((dp[i%2][j][1] + dp[(i-1)%2][j-costs[i]][0])%MOD) + MOD) % MOD;
			}
			if (j - costs[i] - f >= 0) {
				dp[i%2][j][1] = (((dp[i%2][j][1] + dp[(i-1)%2][j-costs[i] - f][1])%MOD) + MOD) % MOD;
			}
		}
	}

	printf("%lld\n", (((dp[n%2][b][0] + dp[n%2][b][1]) % MOD) + MOD) % MOD);;

	return 0;
}