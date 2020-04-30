#include <iostream>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <set>
#include <queue>
#include<map>
#include <utility>

#define MAXN 10001
#define MOD 1000000007

using namespace std;

int main(int argc, char* argv[]) {

	int n;
	scanf("%d", &n);
	int fac[MAXN];
	map<int, int> duplicates;

	fac[0] = 1;
	for (int i = 1; i < MAXN; i++) {
		fac[i] = ((fac[i-1]*i)%MOD + MOD)%MOD;
	}


	for (int i = 0; i < n;i++) {
		int d;
		scanf("%d", &d);
		duplicates[d] += 1;
	}

	int ans = fac[n];
	int prod = 1;
	//printf("%d\n", ans);

	for (pair<int, int> it : duplicates) {
		int times = it.second;
		int number = it.first;
		//printf("%d %d\n", number, times);
		prod = ((prod * fac[times])%MOD + MOD)%MOD;
		//printf("%d\n", ans);
	}

	printf("%d\n", ans/prod);
	return 0;
}