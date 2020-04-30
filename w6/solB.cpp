#include <iostream>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <set>
#include <queue>
#include <map>
#include <utility>

using namespace std;

// Positions of the ship at different days
long long xpos[100001];
long long ypos[100001];
long long n;

// Initial co-ords
long long x1, y1;

// Final co-ords
long long x2, y2;

// Can we reach from start pos to end pos in d days?
bool canDo (long long d) {
	long long curX = x1 + xpos[d%n] + xpos[n]*(d/n);
	long long curY = y1 + ypos[d%n] + ypos[n]*(d/n);

	if (curX == x2 && curY == y2) return true;

	long long diffX = curX > x2 ? curX - x2 : x2 - curX;
	long long diffY = curY > y2 ? curY - y2 : y2 - curY;

	if (diffX + diffY <= d) return true;
	return false;
}

int main() {

	// Take in the initial co-ordinates of the ship
	scanf("%lld %lld", &x1, &y1);

	// Take in the final co-ordinates of the ship
	scanf("%lld %lld", &x2, &y2);

	// Take in the number of characters in the string
	scanf("%lld", &n);

	xpos[0] = 0;
	ypos[0] = 0;

	for (int i = 1; i <= n; i++) {
		char c;
		scanf(" %c", &c);
		if (c == 'U') {
			ypos[i] = ypos[i-1] + 1;
			xpos[i] = xpos[i-1];
		} else if (c == 'D') {
			ypos[i] = ypos[i-1] - 1;
			xpos[i] = xpos[i-1];
		} else if (c == 'L') {
			xpos[i] = xpos[i-1] - 1;
			ypos[i] = ypos[i-1];
		} else if (c == 'R') {
			xpos[i] = xpos[i-1] + 1;
			ypos[i] = ypos[i-1];
		}
	}

	long long diffX = x1 > x2 ? x1 - x2 : x2 - x1;
	long long diffY = y1 > y2 ? y1 - y2 : y2 - y1;

	long long lo = 1;
	long long hi = n*(diffX + diffY);

	long long ans = -1;
	while (lo <= hi) {
		long long mid = (lo + hi)/2;

		if (canDo(mid)) {
			ans = mid;
			hi = mid - 1;
		} else {
			lo = mid + 1;
		}
	}

	printf("%lld\n", ans);

	return 0;
}