#include <iostream>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <set>
#include <queue>
#include <map>
#include <utility>

#define MAXM 100
#define MOD 1000000007


struct Matrix {

	unsigned long long v[MAXM][MAXM];
	int n;

	Matrix(int _n) : n(_n) {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) v[i][j] = 0;
	}

	Matrix operator*(const Matrix &o) const {
		Matrix res(n);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				for (int k = 0; k < n; k++) {
					unsigned long long temp = (v[i][k] * o.v[k][j])%MOD;
					res.v[i][j] = (((res.v[i][j] + temp) % MOD) + MOD)%MOD;
				}
		return res;
	}

	static Matrix getIdentity(int n) {
		Matrix res(n);
		for (int i = 0; i < n; i++) res.v[i][i] = 1;
		return res;
	}

	Matrix operator^(long long k) const {
		Matrix res = Matrix::getIdentity(n);
		Matrix a = *this;

		while (k) {
			if (k%2 == 1) res = res*a;
			a = a*a;
			k /= 2;
		}
		return res;
	}
};

int main() {

	long long N;
	int M;
	scanf("%lld %d", &N, &M);
	Matrix rec(MAXM);
	rec.v[0][0] = 1;
	rec.v[0][M-1] = 1;

	for (int i = 1; i < MAXM; i++) {
		rec.v[i][i-1] = 1;
	}
	rec = rec^N;

	printf("%lld\n", rec.v[0][0]);

	return 0;
}