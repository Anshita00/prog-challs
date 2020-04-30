#include <iostream>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <set>
#include <queue>
#include<map>
#include <utility>

using namespace std;

#define MAXN 200000

int tree[800000];

void update(int a, int v, int i = 1, int start = 0, int end = MAXN) {
	if (end - start == 1) {
		tree[i] = v;
		return;
	}

	int mid = (start + end) / 2;
	if (a < mid) update(a, v, i *2, start, mid);
	else update(a, v, i * 2 + 1, mid, end);

	tree[i] = tree[i*2] == 0 ? tree[i*2+1] : tree[i*2];
}



int main(int argc, char* argv[]) {

	int e;
	scanf("%d", &e);
	map<int, long long> wmap;
	map<long long, int> imap;
	set<long long> widths;
	int k = 0;

	for (int i = 0; i < e; i++) {
		char t;
		scanf(" %c", &t);
		if (t == 'D') {
			long long w,h;
			scanf("%lld %lld", &w, &h);
			wmap[k] = w;
			imap[w] = k;
			widths.insert(w);
			k++;
		} else {
			int j;
			scanf("%d", &j);
			j--;
			long long w = wmap[j];
			auto it = widths.upper_bound(w);
			if (it == widths.end()) {
				printf("RIP\n");
				continue;
			}
			w = *it;
			// printf("%lld\n", w);
			printf("%d\n", imap[w] + 1);
		}
	}

	return 0;
}