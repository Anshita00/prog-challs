#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;

#define MAXN 300000
#define MAXQ 300000

int main() {

	int n,q;
	long long heights[MAXN];
	scanf("%d %d", &n, &q);

	for (int i = 0; i < n; i++) {
		long long d;
		scanf("%lld", &d);
		heights[i] = d;
	}

	for (int i = 0; i < q; i++) {
		char c;
		scanf(" %c", &c);
		if (c == 'U') {
			int l, r;
			long long v;
			scanf("%d %d %lld", &l, &r, &v);
			for (int j = l; j < r; j++) {
				heights[j] += v;
			}
		} else if (c == 'Q') {
			int l,r;
			scanf("%d %d", &l, &r);
			int numSteps = 0;
			for (int j = l + 1; j < r; j++) {
				if (heights[j] > heights[j-1]) {
					numSteps+=1;
				}
			}
			printf("%d\n", numSteps);
		}
	}
./gen.py > random.in; while diff <(./soln < random.in) <(./brute_force < random.in); do echo "all good"; ./gen.py > random.in; done



	return 0;
}