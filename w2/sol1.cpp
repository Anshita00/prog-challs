#include <iostream>
#include<cstring>
#include <sstream>
#include <queue>
#include <set>

using namespace std;

unsigned int tree[600000];
unsigned int MAX_N;

void update (unsigned int a, unsigned int v, bool isOR, unsigned long i = 1, unsigned int start = 1, unsigned int end = MAX_N) {
	// this node ’s range of r e s p o n s i b i l i t y is 1 , so it is a leaf
	if ( end - start == 1) {
		tree [i] = v;
		//printf("WE ARE IN END START IF %d %d \n", end, start);
		return;
	}

	// figure out which child is responsible for the index (a) being updated
	//printf("WE ARE BEFORE UPDATE %d %d %d\n", i, start, end);
	unsigned int mid = ( start + end ) / 2;
	if (a < mid ) 
		update (a, v, !isOR, i * 2, start , mid);
	else
		update (a, v,  !isOR , i * 2 + 1, mid , end);
	// once we have updated the correct child , recalculate our stored value .

	//printf("WE ARE AFTER UPDATE %d %d %d\n", i, start, end);
	if (isOR) {
		tree[i] = tree [i *2] | tree [i *2+1];
	} else {
		tree[i] = tree [i *2] ^ tree [i *2+1];
	}
}

int main()
{

	int n;
	unsigned int m;
	scanf("%u %u", &n, &m);

	for (unsigned long i = 0; i < 600000; i++) {
		tree[i] = 0;
	}


	MAX_N = (1 << n) + 1;
	bool isOR = n % 2 != 0;
	//printf("n is %d\n", n);
	for (unsigned long i = 0; i < MAX_N - 1; i++) {
		//printf("%d\n", i);
		unsigned int temp;
		scanf("%u", &temp);
		// if (isOR) {
		// 	printf(" ISOR\n");
		// 	printf("%lu\n", MAX_N);
		// }
		update(i + 1, temp, isOR);
	}

	for (unsigned int i = 0; i < m; i++) {
		unsigned int p,b;
		scanf("%u %u", &p, &b);
		update(p, b, isOR);
		printf("%u\n", tree[1]);
	}

	return 0;
}