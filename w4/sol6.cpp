#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <limits>
#include <algorithm>

using namespace std;

struct node {
	int maxD;
	long long sumD;
	int firstD;
	int lastD;
	bool incrD;
	bool decrD;
};

#define MAXN 100002;

int N;
node tree[266666];

void init() {
	for (int i = 1; i <= N; i++) {
		node n;
		n.maxD = 0;
		n.sumD = 0;
		n.incrD = false;
		n.decrD = false;
		n.firstD = 0;
		n.lastD = 0;
		tree[i] = n;
	}
}

void update(int a, int v, int i = 1, int start = 1, int end = N + 1) {

	if (end - start == 1) {
		node n;
		n.maxD = v;
		n.sumD = v;
		n.firstD = v;
		n.lastD = v;
		n.incrD = true;
		n.decrD = true;
		tree[i] = n;
		return;
	}

	int mid = (start + end)/2;
	if (a < mid) update(a, v, i*2, start, mid);
	else update(a, v, i*2 + 1, mid, end);

	tree[i].maxD = max(tree[i*2].maxD,tree[i*2+1].maxD);
	tree[i].sumD = tree[i*2].sumD + tree[i*2+1].sumD;
	tree[i].firstD = tree[i*2].firstD;
	tree[i].lastD = tree[i*2+1].lastD;
	tree[i].incrD = tree[i*2].incrD && tree[i*2+1].incrD && tree[i*2].lastD <= tree[i*2+1].firstD;
	tree[i].decrD = tree[i*2].decrD && tree[i*2+1].decrD && tree[i*2].lastD >= tree[i*2+1].firstD;
}

int queryMax(int a, int b, int i = 1, int start = 1, int end = N + 1) {
	if (start == a && end == b) {
		return tree[i].maxD;
	}

	int mid = (start + end)/2;
	int answer = 0;
	if (a < mid) answer = max(answer, queryMax(a, min(b, mid), i * 2, start, mid));
	if (b > mid) answer = answer=max(answer, queryMax(max(a, mid), b, i * 2 + 1, mid, end));

	return answer;

}

long long querySum(int a, int b, int i = 1, int start = 1, int end = N + 1) {
	if (start == a && end == b) {
		return tree[i].sumD;
	}

	int mid = (start + end)/2;
	long long answer = 0;
	if (a < mid) answer += querySum(a, min(b, mid),i * 2, start, mid);
	if (b > mid) answer += querySum(max(a, mid), b, i * 2 + 1, mid, end);

	return answer;
}

bool queryBool(int a, int b, char type, int i = 1, int start = 1, int end = N + 1) {
	if (start == a && end == b) {
		switch (type) {
			case 'I': return tree[i].incrD; break;
			case 'D': return tree[i].decrD; break;
		}
	}

	int mid = (start + end)/2;
	bool res1 = false, res2 = false;

	if (a < mid) res1 = queryBool(a, min(b, mid), type, i * 2, start, mid);
	if (b > mid) res2 = queryBool(max(a, mid), b, type, i * 2 + 1, mid, end);

	if (a < mid && b > mid) {
		bool answer = res1 && res2;
		if (!answer) return answer;
		switch (type) {
			case 'I': return tree[i*2].lastD <= tree[i*2+1].firstD; break;
			case 'D': return tree[i*2].lastD >= tree[i*2+1].firstD; break;
		}
	} else if (a < mid) {
		return res1;
	} else if (b > mid) {
		return res2;
	}

	return false;

}

int main() {

	int M;
	scanf("%d %d", &N, &M);
	init();

	for (int i = 1; i <= N; i++) {
		int temp;
		scanf("%d", &temp);
		update(i, temp);
	}

	for (int i = 0; i < M; i++) {
		char type;
		int x,y;
		scanf(" %c %d %d", &type, &x, &y);

		if (type == 'M') {
			 printf("%d\n", queryMax(x, y+1));
		} else if (type == 'S') {
			printf("%lld\n", querySum(x, y + 1));
		} else if (type == 'I') {
			printf("%d\n", queryBool(x, y + 1, 'I'));
		} else if (type == 'D') {
			printf("%d\n", queryBool(x, y +1, 'D'));
		} else {
			update(x, y);
		}

	}
}
