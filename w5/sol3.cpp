#include <iostream>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <set>
#include <queue>
#include<map>
#include <utility>

using namespace std;

#define MAXN 200005
#define INF 200000000005

long long noRouter[4*MAXN];
long long withRouter[4*MAXN]; 
int n;


void init() {
	for (int i = 0; i < 4*MAXN; i++) {
		noRouter[i] = INF;
		withRouter[i] = INF;
	}
}

void update(int a, long long v, int type, int i = 1, int start = 1, int end = n + 1) {
	if (end - start == 1) {
		if (type == 0) {
			noRouter[i] = v;
		} else {
			withRouter[i] = v;
		}
		return;
	}
	int mid = (start + end)/2;
	if (a < mid) update(a, v, type, i * 2, start, mid);
	else update(a, v, type, i * 2 + 1, mid, end);

	if (type == 0) {
		noRouter[i] = noRouter[i*2] < noRouter[i * 2 + 1] ? noRouter[i*2] : noRouter[i * 2 + 1];
	} else {
		withRouter[i] = withRouter[i*2] < withRouter[i*2+1] ? withRouter[i*2] : withRouter[i*2+1];
	}

}


long long query(int a, int b, int type, int i = 1, int start = 1, int end = n + 1) {
	if (start == a && end == b) {
		if (type == 0) {
			return noRouter[i];
		} else {
			return withRouter[i];
		}
	}
	int mid = (start + end)/2;
	long long answer = INF;

	if (a < mid) answer = query(a, min(b, mid), type, i * 2, start, mid);
	if (b > mid) answer = min(answer, query(max(a, mid), b,  type, i * 2 + 1, mid, end));

	return answer;
}


int main() {
	int k;
	scanf("%d %d", &n, &k);
	long long dp[MAXN][2];
	init();

	long long minCost = 0;
	dp[0][0] = 1;
	dp[0][1] = 1;
	dp[n-1][1] = INF;

	for (int i = 0; i < n; i++) {
		char cur;
		scanf(" %c", &cur);

		// If there's no place for router, or if there's one but we don't place it
		// we can either just simply place a connection
		// or if there's a router in the range previously, we can use it
		// We choose whatever is more efficient
		if (i != 0) {
			if (i - k <= 0) {
				dp[i][0] = min(dp[i-1][0] + i + 1, query(1, i + 1, 1));
			} else {
				dp[i][0] = min(dp[i-1][0] + i + 1, query(i-k + 1, i + 1, 1));
			}
		}

		// After adding the connection, we need to update the range tree
		update(i + 1, dp[i][0], 0);

		// If there's place for a router, then we can choose to place it
		if (cur == '1') {
			dp[i][1] = i + 1;
			if (i - k >= 1) {
				dp[i][1] += min(query(i-k, i + 1, 1), query(i - k, i + 1, 0));
			}
			update(i + 1, dp[i][1], 1);

		}
	}

	printf("%lld\n", min(dp[n-1][1], dp[n-1][0]));

	return 0;
}