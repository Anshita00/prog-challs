#include <iostream>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <set>
#include <queue>
#include<map>
#include <utility>


#define MAXN 2000
#define INF 5000000000000

using namespace std;

int main(int argc, char* argv[]) {

	int n,k;
	long long coords[MAXN];
	long long cum[MAXN];
	scanf("%d %d", &n, &k);

	for (int i = 0; i < n; i++) {
		long long d;
		scanf("%lld", &d);
		coords[i] = d;
		cum[i] = d;
		if (i != 0) {
			cum[i] += cum[i-1];
		}
	}

	long long minCost = INF;
	for (int i = 0 ; i <= n; i++) {
		if (i == 0) continue;
		long long curCost = 0;
		long long minMineCost = INF;
		for (int j = 0 ; j < i; i++) {
			long long minePos = coords[j];
			long long curMineCost = (j+1)*minePos - cum[j];
			curMineCost += cum[(i - j - 1)
			minMineCost = min(minMineCost, curMineCost); 
		}
		for (int j = i; j < n; j++) {

		}
	}

	return 0;
}