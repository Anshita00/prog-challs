#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;

#define MAXN 300000
#define MAXQ 300000

struct node {
	long long rightHeight;
	long long leftHeight;
	int numSteps;
};

node tree[1200000];
long long lazyset[1200000];


void propogate(int i) {
	lazyset[i*2] += lazyset[i];
	lazyset[i*2+1] += lazyset[i];
	tree[i*2].rightHeight += lazyset[i];
	tree[i*2].leftHeight += lazyset[i];
	tree[i*2+1].rightHeight += lazyset[i];
	tree[i*2+1].leftHeight += lazyset[i];
	lazyset[i] = 0;
}

void recalculate(int i) {

	tree[i].numSteps = tree[i*2].numSteps + tree[i*2+1].numSteps;
	if (tree[i*2+1].leftHeight > tree[i*2].rightHeight) {
		tree[i].numSteps += 1;
	}
	tree[i].rightHeight = tree[i*2+1].rightHeight;
	tree[i].leftHeight = tree[i*2].leftHeight;
}

void update(int uL, int uR, long long v, int i = 1, int start = 0, int end = MAXN) {
	if (uL == start && uR == end) {
		tree[i].rightHeight += v;
		tree[i].leftHeight += v;
		lazyset[i] += v;
		return;
	}

	propogate(i);

	int mid = (start + end) / 2;
	if (uL < mid) update(uL, min(uR, mid), v, i * 2, start, mid);
	if (uR > mid) update(max(uL, mid), uR, v, i * 2 + 1, mid, end);

	recalculate(i);

}

node query(int a, int b, int i = 1, int start = 0, int end = MAXN) {

	if (start == a && end == b) return tree[i];

	propogate(i);

	int mid = (start + end) / 2;

	node tempAnswer;
	node answer;

	if (a < mid && b <= mid) return query(a, min(b, mid), i * 2, start, mid);
	if (a >= mid && b > mid) return query(max(a, mid), b, i * 2 + 1, mid, end);
	if (a < mid && b > mid) {
		tempAnswer = query(a, min(b, mid), i * 2, start, mid);
		answer = query(max(a, mid), b, i * 2 + 1, mid, end);
		answer.numSteps += tempAnswer.numSteps;
		if (tempAnswer.rightHeight < answer.leftHeight) {
			answer.numSteps += 1;
		}
		answer.leftHeight = tempAnswer.leftHeight;
	}
	return answer;
}

int main(int argc, char* argv[]) {

	int n,q;
	scanf("%d %d", &n, &q);

	for (int i = 0; i < n; i++) {
		long long d;
		scanf("%lld", &d);
		update(i, i + 1, d);
	}

	for (int i = 0; i < q; i++) {
		char c;
		scanf(" %c", &c);
		if (c == 'U') {
			int l, r;
			long long v;
			scanf("%d %d %lld", &l, &r, &v);
			update(l, r, v);
		} else if (c == 'Q') {
			int l,r;
			scanf("%d %d", &l, &r);
			node result = query(l, r);
			printf("%d\n", result.numSteps);
		}
	}

	return 0;
}