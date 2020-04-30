#include <iostream>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <set>
#include <queue>
#include <map>
#include <utility>

#define MAXN 100005
#define MOD 1000000007

using namespace std;

int n;
int t;
long long a[MAXN];

long long pow(long long x, long long k) {
	if (k == 0) return 1;

	long long a = pow(x, ((k/2)%MOD + MOD) % MOD);
	a = ((a*a) % MOD + MOD) % MOD;
	if (k % 2 == 1) a = ((a*x % MOD) + MOD) % MOD;
	return a;
}

int main() {

	scanf("%d", &t);
	while (t--) {

		scanf("%d", &n);

		for (int i = 0; i < n; i++) {
			scanf("%lld", &a[i]);
		}
		sort(a, a+n);

		long long max = 0;
		long long min = 0;
		for (int i = 0; i < n; i++) {
			long long temp = (a[i] * pow(2, i)) % MOD;
			max = (((temp + max)%MOD) + MOD)%MOD;
			temp = (a[i] * pow(2, n - i - 1)) % MOD;
			min = (((temp + min)%MOD) + MOD) % MOD;
		}

		long long finalAns = (((max - min)%MOD) + MOD)%MOD;
		printf("%lld\n", finalAns);
	}
	return 0;
}