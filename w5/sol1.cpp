#include <iostream>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <set>
#include <queue>
#include<map>
#include <utility>
 
#define MAXN 200005
 
using namespace std;

int main() {
	int n;
	long long a[31];
	long long b[31];
	scanf("%d", &n);

	while (n != -1) {
		a[0] = 1;
		b[0] = 0;
		a[1] = 0;
		b[1] = 1;
		for (int i = 2; i <= n; i++) {
			a[i] = a[i-2] + 2*b[i-1];
			b[i] = a[i-1] + b[i-2];
		}
		printf("%lld\n", a[n]);
		scanf("%d",&n);
	}
}