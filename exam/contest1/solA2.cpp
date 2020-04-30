#include <iostream>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <set>
#include <queue>
#include <map>
#include <utility>

using namespace std;
vector<tuple<bool, int, int> > events[500005];
multiset<int> subjects[1000005];

int main() {
	int N, D;
	scanf("%d %d", &N, &D);
	for (int i = 0; i < 1000005; i++) subjects[i].insert(0);
	for (int i = 0; i < N; i++) {
		int s, e, v, c;
		scanf("%d %d %d %d", &s, &e, &v, &c);
		events[s].emplace_back(true, v, c);
		events[e].emplace_back(false, v, c);
	}

	int T = 0;
	for (int d = 0; d < D; ++d) {
		for (auto p: events[d]) {
			int v = get<1>(p);
			int c = get<2>(p);

			T -= *prev(subjects[c].end());
			if (get<0>(p)) {
				subjects[c].insert(v);
			} else {
				subjects[c].erase(subjects[c].find(v));
			}
			T += *prev(subjects[c].end());
		}
		printf("%d\n", T);
	}

}