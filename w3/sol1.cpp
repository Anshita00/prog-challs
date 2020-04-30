#include <iostream>
#include<cstring>
#include <sstream>
#include <queue> 

using namespace std;

int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

struct edge {
	int i;
	int j;
	int weight;

	bool operator> (const edge &e) const {
		return this->weight > e.weight;
	}
};



int min(int a, int b) {
	if (a == 20000 && b != 20000) return b;
	if (b == 20000 && a != 20000) return a;
	if (a == 20000 && b == 20000) return 0;
	return a < b ? a : b;
}

int findMinimum(int n, int m, int maze[999][999]) {
	priority_queue <edge, vector <edge>, greater <edge>> pq;
	int cost[999][999];

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cost[i][j] = -1;
		}
	}

	edge e;
	e.i = 0;
	e.j = 0;
	e.weight = maze[0][0];
	pq.push(e);
	cost[0][0] = maze[0][0];

	while (!pq.empty()) {
		edge cur = pq.top();
		pq.pop();

        for (int i = 0; i < 4; ++i) {
            int r = cur.i + dx[i];
            int c = cur.j + dy[i];
            if (r < 0 || r >= n || c < 0 || c >= m)
                continue;
            if (cost[r][c] == -1
                || cost[cur.i][cur.j] + maze[r][c] < cost[r][c])
            {
                cost[r][c] = cost[cur.i][cur.j] + maze[r][c];
                e.i = r;
                e.j = c;
                e.weight = cost[r][c];
                pq.push(e);
            }
        }

	}
	return cost[n-1][m-1];
}

int main() {
	unsigned int T;
	scanf("%u", &T);
	while (T--) {
		int R,C;
        int maze[999][999];

		scanf("%d", &R);
		scanf("%d", &C);
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				int temp;
				scanf("%d",&temp);
				maze[i][j] = temp;
			}
		}
		printf("%d\n", findMinimum(R, C, maze));
	}
	return 0;
}