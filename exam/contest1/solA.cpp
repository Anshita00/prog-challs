#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;

#define MAXN 200000
#define MAXQ 200000

int n,q;

struct node {
	int price;
	int volume;
	int maxVal;
	bool embargo = false;
};

node tree[800000];

void updatePrice(int a, int v, int i = 1, int start = 1, int end = MAXN + 1) {
	if (end - start == 1) {
		tree[i].price = v;
		if (tree[i].embargo == false) {
			tree[i].maxVal = v * tree[i].volume;
		}
		return;
	}

	int mid = (start + end) / 2;
	if (a < mid) updatePrice(a, v, i * 2, start, mid);
	else updatePrice(a, v, i * 2 + 1, mid, end);

	tree[i].maxVal = max(tree[i*2].maxVal, tree[i*2+1].maxVal);
}

void updateVolume(int a, int v, int i = 1, int start = 1, int end = MAXN + 1) {
	if (end - start == 1) {
		tree[i].volume = v;
		if (tree[i].embargo == false) {
			tree[i].maxVal = v * tree[i].price;
		}
		return;
	}

	int mid = (start + end) / 2;
	if (a < mid) updateVolume(a, v, i * 2, start, mid);
	else updateVolume(a, v, i * 2 + 1, mid, end);

	tree[i].maxVal = max(tree[i*2].maxVal, tree[i*2+1].maxVal);
}

void embargo (int a, int i = 1, int start = 1, int end = MAXN + 1) {

	if (end - start == 1) {
		tree[i].embargo = true;
		tree[i].maxVal = 0;
		return;
	}

	int mid = (start + end) / 2;
	if (a < mid) embargo(a, i * 2, start, mid);
	else embargo(a,i * 2 + 1, mid, end);

	tree[i].maxVal = max(tree[i*2].maxVal, tree[i*2+1].maxVal);
}

void dembargo (int a, int i = 1, int start = 1, int end = MAXN + 1) {

	if (end - start == 1) {
		tree[i].embargo = false;
		tree[i].maxVal = tree[i].volume * tree[i].price;
		return;
	}

	int mid = (start + end) / 2;
	if (a < mid) dembargo(a,i * 2, start, mid);
	else dembargo(a, i * 2 + 1, mid, end);

	tree[i].maxVal = max(tree[i*2].maxVal, tree[i*2+1].maxVal);
}

int main(int argc, char *argv[]) {

	scanf("%d %d", &n, &q);

	for (int i = 1; i <= n; i++) {
		int d;
		scanf("%d", &d);
		updatePrice(i, d);
	}

	for (int i = 1; i <= n; i++) {
		int d;
		scanf("%d", &d);
		updateVolume(i, d);
	}


	for (int i = 0; i < q; i++) {
		char t;
		scanf(" %c", &t);
		if (t == 'F') {
			printf("%d\n", tree[1].maxVal);
		} else if (t == 'P') {
			int n, p;
			scanf("%d %d", &n, &p);
			updatePrice(n, p);
		} else if (t == 'V') {
			int n, v;
			scanf("%d %d", &n, &v);
			updateVolume(n, v);
		} else if (t == 'D') {
			int n;
			scanf("%d", &n);
			dembargo(n);
		} else if (t == 'E') {
			int n;
			scanf("%d", &n);
			embargo(n);
		}
 	}
	return 0;
}