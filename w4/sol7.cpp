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
 
int N;
 
struct node {
	set<long long> rt;
	long long x;
	int i;
};
 
node rt[4*MAXN];
 
void init() {
	for (int i = 0; i <= 4*MAXN; i++) {
		rt[i] = { {}, -1, -1};
	}
}
 
 
void update(int type, int a, long long x, long long y, int i = 1, int start = 1, int end = N + 1) {
 
	if (end - start == 1) {
		if (type == 1) {
			rt[i].x = x;
			rt[i].i = i;
			rt[i].rt.insert(y);
		} else {
			rt[i].rt.erase(y);
			if (rt[i].rt.empty()) {
				rt[i].x = -1;
				rt[i].i = -1;
			}
		}
		return;
	}
 
	int mid = (start + end)/2;
	if (a < mid) update(type, a, x, y, i * 2, start, mid);
	else update(type, a, x, y, i * 2 + 1, mid, end);
 
	rt[i].x = rt[i*2].x;
	if (rt[i].x != -1) {
		rt[i].i = rt[i*2].i;
	} else {
		rt[i].x = rt[i*2+1].x;
		rt[i].i = rt[i*2+1].i;
	}
}
 
pair<long long, long long> query(int a, int b, long long x, long long y, int i = 1, int start = 1, int end = N + 1) {
	if (start == a && end == b) {
		if (rt[i].x == -1) {
			return make_pair(-1, -1);
		}
		auto it = rt[rt[i].i].rt.upper_bound(y);
		if (it == rt[rt[i].i].rt.end()) {
			if (end - start == 1) {
				return make_pair(-1, -1);
			}
		} else {
			return make_pair(rt[rt[i].i].x, *it);
		}
	}
	int mid = (start + end)/2;
	pair<long long, long long> answer = make_pair(-1, -1);
 
	if (a < mid) answer = query(a, min(b, mid), x, y, i * 2, start, mid);
	if (answer.first == -1 && b > mid) answer = query(max(a, mid), b, x, y, i * 2 + 1, mid, end);
	return answer;
}
 
int main() {
 
	scanf("%d", &N);
	long long xsCopy[MAXN+5];
	map<long long, int> xCompressed;
	set<long long> seenX;
	vector<long long> xs;
	long long xCopy[MAXN + 5];
	vector<long long> ys;
	vector<char> operation;
 
	init();
	int j = 0;
	for (int i = 0; i < N; i++) {
		long long x,y;
		char ins[10];
		scanf(" %s", ins);
		if (ins[0] == 'a') {
			scanf("%lld %lld", &x, &y);
			//update(1, x, x, y);
			operation.push_back('a');
			xs.push_back(x);
			if (seenX.find(x) == seenX.end()) {
				xCopy[j] = x;
				j++;
				seenX.insert(x);
			}  
			ys.push_back(y);
		} else if (ins[0] == 'f') {
			scanf("%lld %lld", &x, &y);
			// pair<long long, long long> res = query(x + 1, N + 1, y);
			// if (res.first == -1) {
			// 	printf("-1\n");
			// } else {
			// 	printf("%lld %lld\n", res.first, res.second);
			// }
			operation.push_back('f');
			xs.push_back(x);
			ys.push_back(y);
		} else if (ins[0] == 'r') {
			scanf("%lld %lld", &x, &y);
			//update(2, x, x, y);
			operation.push_back('r');
			xs.push_back(x);
			ys.push_back(y);
		}
	}
 
	int size = j;
	sort(xCopy, xCopy + size);
 
	for (unsigned int i = 0; i < size; i++) {
		xCompressed.insert({ xCopy[i], i+1 });
	}
 
	for (int i = 0; i < N; i++) {
		long long x,y;
		if (operation.at(i) == 'a') {
			x = xs.at(i);
			y = ys.at(i);
			auto result = xCompressed.find(x);
			update(1, result->second, x, y);
		} else if (operation.at(i) == 'f') {
			// scanf("%lld %lld", &x, &y);
			x = xs.at(i);
			y = ys.at(i);
			auto result = xCompressed.lower_bound(x);
			pair<long long, long long> res;
			if (result->second <= 0) {
				printf("-1\n");
				continue;
			} else if (result -> first > x) {
		 		res = query(result->second, N + 1, x, y);
			} else {
		 		res = query(result->second + 1, N + 1, x, y);
			}
			if (res.first == -1) {
				printf("-1\n");
			} else {
				printf("%lld %lld\n", res.first, res.second);
			}
		} else if (operation.at(i) == 'r') {
			x = xs.at(i);
			y = ys.at(i);
			auto result = xCompressed.find(x);
			update(2, result->second, x, y);
		}
	}
 
	return 0;
}