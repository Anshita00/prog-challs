#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <limits>
#include <algorithm>
using namespace std;

#define MAX_N 100001
long long lazyadd[266666];
int mod0[266666];
int mod1[266666];
int mod2[266666];
int n;

void swapMods(int id, int type) {
	if (type == 0) {
		return;
	}
	if (type == 1) {
		int temp = mod0[id];
		mod0[id] = mod2[id];
		mod2[id] = mod1[id];
		mod1[id] = temp;
		return;
	}
	if (type == 2) {
		int temp = mod0[id];
		mod0[id] = mod1[id];
		mod1[id] = mod2[id];
		mod2[id] = temp;
		return;
	}
}

void recalculate(int id, long long l, long long r) {
	if (r - l == 1) return;
	mod0[id] = mod0[id * 2] + mod0[id * 2 + 1];
	mod1[id] = mod1[id * 2] + mod1[id * 2 + 1];
	mod2[id] = mod2[id * 2] + mod2[id * 2 + 1];
}

void update_lazy(int id, long long v,long long l, long long r) {
	lazyadd[id] += v;
	int modulus = v % 3;
	if (modulus == 0) {
		swapMods(id, 0);
	} else if (modulus == 1) {
		swapMods(id, 1);
	} else {
		swapMods (id, 2);
	}

	// recalculate(id, l, r);
}

void propogate(int i, int l, int r) {
	long long mid = (l + r)/2;
	update_lazy(i * 2,lazyadd[i], l, mid);
	update_lazy(i * 2 + 1, lazyadd[i], mid, r);
	lazyadd[i] = 0;
}

void update (int uL, int uR, int i = 1, int cLeft = 1, int cRight = n + 1) {
	if (uL == cLeft and uR == cRight) {
		update_lazy(i, 1, cLeft, cRight);
		return;
	}

	propogate(i, cLeft, cRight);
	int mid = (cLeft + cRight)/2;
	if (uL < mid) update(uL, min(uR, mid), i * 2, cLeft, mid);
	if (uR > mid) update(max(uL, mid), uR, i * 2 + 1, mid, cRight);
	recalculate(i, cLeft, cRight);
}

int query(int qL, int qR, int i = 1, int cLeft = 1, int cRight = n + 1) {
	if (qL == cLeft && qR == cRight) {
		return mod0[i];
	}
	propogate(i, cLeft, cRight);
	int mid = (cLeft + cRight) / 2;
	long long ans = 0;
	if (qL < mid) ans += query(qL, min(qR, mid), i * 2, cLeft, mid);
	if (qR > mid) ans += query(max(qL, mid), qR, i * 2 + 1, mid, cRight);
	return ans;
}

void init(int cL, int cR, int i = 1) {
	if (cR - cL != 1) {
		int mid = (cL + cR)/2;
		if (cL < mid) init(cL, min(mid, cR), i * 2);
		if (cR > mid) init(max(cL, mid), cR, i * 2 + 1);
		mod0[i] = mod0[i * 2] + mod0[i * 2 + 1];
		mod1[i] = mod1[i * 2] + mod1[i * 2 + 1];
		mod2[i] = mod2[i * 2] + mod2[i * 2 + 1];
	} else {
		mod0[i] = 1;
		mod1[i] = 0;
		mod2[i] = 0;
	}
}

int main() {
	int q;
	scanf("%d %d", &n, &q);
	init(1, n + 1);
	// printf("%d\n", query(1, n + 1));
	for (int i = 0; i < q; i++) {
		int type, a, b;
		scanf("%d %d %d", &type, &a, &b);
		if (type == 0) {
			update(a + 1, b + 2);
		} else {
			int result = query(a + 1, b + 2);
			printf("%d\n", result);
		}
	}

}