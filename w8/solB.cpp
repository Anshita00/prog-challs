#include <iostream>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <set>
#include <queue>
#include <map>
#include <utility>

using namespace std;

set<long long> facs;

void primefactorize(long long x) {
	for (long long f = 2; f*f <= x; f++) {
		while (x % f == 0) {
			facs.insert(f);
			x /= f;
		}
	}
	if (x != 1) {
		facs.insert(x);
	}
}


int main() {

	long long n;
	scanf("%lld", &n);
	primefactorize(n);
	long long totalProduct = 1;
	for (auto it = facs.begin(); it != facs.end(); it++) {
		totalProduct *= *it;
	}

	long long numTimes = 0;
	long long i;
	for (i = totalProduct; i%n != 0; i*=i) numTimes ++;
	if (i > n) {
		numTimes++;
	}
	printf("%lld %lld\n", totalProduct, numTimes);

	return 0;
}

