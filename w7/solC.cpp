#include <iostream>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <set>
#include <queue>
#include <map>
#include <utility>

#define N 100000

using namespace std;

struct line { long long m, b; };

// long long floordiv(long long a, long long b) {
// 	return a / b - (a%b && ((a < 0) ^ (b < 0)));
// }

long long intersect(line a, line b) {
	//floordiv(b.b - a.b, a.m - b.m);
	return (b.b - a.b) / (a.m - b.m);
}

// double intersect(line a, lint b) {
// 	return (double)(b.b - a.b)/(a.m - b.m);
// }

vector<line> cht;
int cp;

void add(line l) {
	auto n = cht.size();
	while (n >= 2 &&
			intersect(cht[n-1], cht[n-2]) >= intersect(cht[n-1], l)) {
		cht.pop_back();
		n = cht.size();
	}
	cht.push_back(l);
	cp = min(cp, (int)cht.size() - 1);
}

long long query(long long x) {
	while (cp+1 != cht.size() && intersect(cht[cp], cht[cp+1]) < x) cp++;
	return cht[cp].m*x + cht[cp].b;
}

int main() {

	int n;
	scanf("%d", &n);
	long long a[N];
	long long b[N];
	long long dp[N];

	for (int i = 0; i < n; i++) {
		long long t;
		scanf("%lld", &t);
		a[i] = t;
	}

	for (int i = 0; i < n; i++) {
		long long t;
		scanf("%lld", &t);
		b[i] = t;
	}

	for (int i = 0; i < n; i++) {
		// dp[i] = min(j < i) dp[j] + b[j] * a[i]
		
		dp[i] = (i == 0) ? 0 : query(a[i]);
		line l;
		l.m = b[i];
		l.b = dp[i];
		add(l);
	}

	printf("%lld\n", dp[n-1]);
	return 0;
}
