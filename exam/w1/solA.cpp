#include <stdlib.h>
#include <stdio.h>

using namespace std;

#define MAXN 10000000

int main() {

	int n;

	scanf("%d", &n);
	long long numWays = 0;
	long long curSum = 0;
	int firstNumber = 1;

	for (int i = 1; i <= n; i++) {
		curSum += i;
		while (curSum - firstNumber >= n) {
			curSum -= firstNumber;
			firstNumber ++;
		}
		if (curSum == n) numWays++;
	}

	printf("%lld\n", numWays);

	return 0;
}