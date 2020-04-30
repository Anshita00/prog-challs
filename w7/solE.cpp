#include <iostream>
#include <cstring>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <set>
#include <queue>
#include <map>
#include <utility>

#define MAXN 1000000

using namespace std;

struct node {
	long long x;
	long long y;
	long long a;

	bool operator<(const node& b) const {
		return x < b.x;
	}
};

struct line { long long m, b; };

double intersect(line a, line b) {
	return (double)(b.b - a.b) / (a.m - b.m);
}
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

// long long query(long long x) {
// 	int lo = 0; int hi = cht.size() - 2;
// 	int idx = cht.size() - 1;
// 	while (lo <= hi) {
// 		int mid = (lo + hi)/2;
// 		if (intersect(cht[mid], cht[mid+1]) >= x) {
// 			idx = mid;
// 			hi = mid - 1;
// 		} else {
// 			lo = mid + 1;
// 		}
// 	}

// 	return cht[idx].m*x + cht[idx].b;
// }

long long query(long long x) {
	while (cp+1 != cht.size() && intersect(cht[cp], cht[cp+1]) < x) cp++;
	return cht[cp].m*x + cht[cp].b;
}


int main() {
	int n;
	long long dp[MAXN+1];
	scanf("%d", &n);
	long long maxVal = -1000000000000000000;
	vector<node> rects;

	for (int i = 0; i < n; i++) {
		long long curX, curY;
		long long curA;
		scanf("%lld %lld %lld", &curX, &curY, &curA);
		node n = {curX, curY, curA};
		rects.push_back(n);
	}
	sort(rects.begin(), rects.end());

	for (int i = 0; i < n ; i++) {
		long long optA = rects[i].x*rects[i].y - rects[i].a;
		long long optB = (i == 0 ? 0 : query(-rects[i].y)) -  rects[i].a + rects[i].y*rects[i].x;
		dp[i] =  max(optA, optB);
		if (dp[i] > maxVal) {
			maxVal = dp[i];
		}
		line l;
		l.m = rects[i].x;
		l.b = dp[i];
		add(l);
	}

	printf("%lld\n", maxVal);

	return 0;
}