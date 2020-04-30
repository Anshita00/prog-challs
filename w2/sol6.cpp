#include <iostream>
#include<cstring>
#include <sstream>
#include <queue>

#define MAXN 100002
#define MODULO 1000000007

using namespace std;

int main() {
	int n,q;
	long long f[MAXN];
	scanf("%d %d", &n, &q);
	long long f1, f2;
	scanf("%lld %lld", &f1, &f2);
	long long a, b;
	scanf("%lld %lld", &a, &b);
	long long v[MAXN];
	long long d[MAXN];

	for (int i = 0; i < n; i++) {
		long long temp;
		scanf("%lld", &temp);
		v[i] = temp;
		d[i] = 0;
	}
	d[n] = 0;
	d[n + 1] = 0;

	f[0] = f1;
	f[1] = f2;
	for (int i = 2; i <= n + 1; i++) {
		f[i] = (((a*f[i-2]) % MODULO) + ((b*f[i-1]) % MODULO)) % MODULO;
	}

	for (int i = 0; i < q; i++) {
		int l, r;
		scanf("%d %d", &l, &r);
		l--;
		r--;
		if (r - l == 0) {
			d[l] = (d[l] + f[0]) % MODULO;
			d[r+1] = ((d[r+ 1] - ((b*f[0])% MODULO)) + MODULO) % MODULO;
			d[r+2] = ((d[r+2] -  ((a*f[0]) % MODULO)) + MODULO) % MODULO;
		} else {
			d[l] = (d[l] + f[0]) % MODULO;
			d[l + 1] = ((((f[1] - ((b*f[0]) % MODULO)) + MODULO) % MODULO) + d[l+1] + MODULO) % MODULO;
			d[r + 1] = (d[r+1] - f[r - l + 1] + MODULO) % MODULO;
			// d[r+1] = (((((((-a*f[r-l - 1]) % MODULO) - ((b*f[r - l]) % MODULO))) + MODULO) % MODULO) + d[r+1]) % MODULO;
			d[r+2] = (((d[r+2] -  ((a*f[r - l])) + MODULO) % MODULO)) % MODULO;
		}
	}

	for (int i = 0; i < n; i++) {
		if (i == 0) {
			v[i] = (v[i] + d[i] + MODULO) % MODULO;
		} else if (i == 1) {
			d[i] = (d[i] + ((b*d[i-1]) % MODULO) + MODULO) % MODULO;
			v[i] = (d[i] + v[i] + MODULO) % MODULO;
		} else {
			d[i] = (((((a*d[i-2]) % MODULO) + ((b*d[i-1]) % MODULO)) % MODULO) + d[i] + MODULO) % MODULO;
			v[i] = (d[i] + v[i] + MODULO) % MODULO;
		}
	}

	for (int i = 0; i < n; i++) {
		printf("%lld ", v[i]);
	}
	printf("\n");

}