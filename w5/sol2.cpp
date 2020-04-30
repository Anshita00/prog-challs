#include <iostream>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <set>
#include <queue>
#include<map>
#include <utility>


#define INF 1000000000000
#define MAXN 100
#define MAXM 100
 
using namespace std;

int main() {

	int n, m, k;
	scanf("%d %d %d", &n, &m, &k);
	long long dp[MAXN][MAXM][MAXN];
	long long paints[MAXN][MAXM];
	int colours[MAXN];

	for (int i = 0; i < MAXN; i++) {
		for (int j = 0; j < MAXM; j++) {
			for (int k = 0; k < MAXN; k++) {
				dp[i][j][k] = 0;
				dp[i][j][k] = 0;
			}
		}
	}

	for (int i = 0; i < n; i++) {
		int ci;
		scanf("%d", &ci);
		colours[i] = ci - 1;
	}


	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			long long p;
			scanf("%lld", &p);
			paints[i][j] = p;
		}
	}

	if (colours[0] == -1) {
		for (int j = 0; j < m; j++) {
			dp[0][j][0] = paints[0][j];
			for (int k = 1; k < n; k++) {
				dp[0][j][k] = INF;
			} 
		}
	} else {
		for (int j = 0; j < m; j++) {
			if (j == colours[0]) {
				dp[0][j][0] = 0;
				for (int k = 1; k < n; k++) {
					dp[0][j][k] = INF;
				} 
			} else {
				for (int k = 0; k < n; k++) {
					dp[0][j][k] = INF;
				} 
			}
		}
	}

	for (int i = 1; i < n; i++) {
		for (int j = 0; j < m; j++) {
			for (int k = 0; k < n; k++) {
			 	if (colours[i] != -1 && j != colours[i]) {
					dp[i][j][k] = INF;
					continue;
				}
				if (k == 0) {
					dp[i][j][k] = dp[i-1][j][k]  + paints[i][j];
				} else {
					long long minCost = INF;
					for (int l = 0; l < m; l++) {
						if (l == j) continue;
						if (dp[i-1][l][k-1] < minCost) {
							minCost = dp[i-1][l][k-1];
						}
					}
					if (minCost < dp[i-1][j][k]) {
						dp[i][j][k] = minCost + paints[i][j];
					} else {
						dp[i][j][k] = dp[i-1][j][k] + paints[i][j];
					}
				}
				if (colours[i] != -1) {
					dp[i][j][k] = dp[i][j][k] - paints[i][j];
				}
			}
		}
	}

	long long minCost = INF;
	for (int j = 0; j < m; j++) {
		if (dp[n-1][j][k-1] < minCost) {
			minCost = dp[n-1][j][k-1];
		}
	}

	if (minCost != INF) {
		printf("%lld\n", minCost);
	} else {
		printf("-1\n");
	}

	return 0;	
}