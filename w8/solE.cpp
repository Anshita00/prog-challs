#include <iostream>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <set>
#include <queue>
#include <map>
#include <utility>

#define MAXK 1000
#define MOD 1000000007

using namespace std;

int k;
long long colours[MAXK];

long long f[MAXK];

long long modpow(long long x, long long k) {
	if (k == 0) return 1;

	long long a = modpow(x, k/2);
	a = (a * a) % MOD;
	if (k % 2 == 1) a = (a * x) % MOD;
	return a;
}

long long inv(long long x) {
	return modpow(x, MOD-2);
}

int main() {
	scanf("%d", &k);

	f[0] = 1;
	for (int i = 1; i < MAXK; i++) f[i] = (i * f[i-1]) % MOD;

	long long total = 0;
	for (int i = 0; i < k; i++) {
		long long c;
		scanf("%lld", &c);
		colours[i] = c;
		total += c;
	}

	long long ans = 1;

	for (int i = k - 1; i >= 0; i--) {
		long long n = total - 1;
		long long k = colours[i] - 1;
		long long res = (f[n] * inv(f[n-k])) % MOD;
		res = (res * inv(f[k])) % MOD;
		ans = (ans * res) % MOD;
		total -= colours[i];
	}

	printf("%lld\n", ans);

	return 0;
}