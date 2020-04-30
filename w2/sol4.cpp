#include <iostream>
#include<cstring>
#include <sstream>
#include <queue> 
// #include <set>
#include <bits/stdc++.h>
// #include <map>

using namespace std;

long long parent[5000005];
long long subtree_size[5000005];
long long secondPopulation[5000005];
long long population[5000005];
multiset<long long> maxPopulation;

long long root(long long x) {
	return parent[x] == x ? x : parent[x] = root(parent[x]);
}

void join(long long x, long long y) {
	x = root(x);
	y = root(y);

	if (x == y) return;

	if (subtree_size[x] < subtree_size[y]) {
		parent[x] = y;
		subtree_size[y] += subtree_size[x];
		auto yPopIt = maxPopulation.find(-1 * population[y]);
		long long yPop = *yPopIt;
		maxPopulation.erase(yPopIt);
		auto xPopIt = maxPopulation.find(-1 * population[x]);
		long long xPop = *xPopIt;
		maxPopulation.erase(xPopIt);
		maxPopulation.insert(xPop + yPop);
		population[y] += population[x];
	} else {
		parent[y] = x;
		subtree_size[x] += subtree_size[y];
		auto yPopIt = maxPopulation.find(-1 * population[y]);
		long long yPop = *yPopIt;
		maxPopulation.erase(yPopIt);
		auto xPopIt = maxPopulation.find(-1 * population[x]);
		long long xPop = *xPopIt;
		maxPopulation.erase(xPopIt);
		maxPopulation.insert(xPop + yPop);
		population[x] += population[y];
	}
}

int main()
{
	int n, m, q;
	multimap<long long, pair<long long, long long>> roads;
	vector<tuple<char, long long, long long>> queries;
	vector<long long> output;
	scanf("%d %d %d", &n, &m, &q);

	for (int i = 1; i <= n; i++) {
		parent[i] = i;
		subtree_size[i] = 1;
		population[i] = 0;
		secondPopulation[i] = 0;
	}

	for (int i = 1; i <= n; i++) {
		long long temp;
		scanf("%lld", &temp);
		population[i] = temp;
		secondPopulation[i] = temp;
		maxPopulation.insert(-1*temp);
	}

	for (int i = 1; i <= m; i++) {
		int x, y;
		scanf("%d %d\n", &x, &y);
		roads.insert({i, make_pair(x, y)});
	}

	for (int i = 0; i < q; i++) {
		char c;
		long long second;
		scanf(" %c %lld", &c, &second);
		if (c == 'P') {
			long long x;
			scanf(" %lld", &x);
			long long temp = population[second];
			population[second] = x;
			secondPopulation[second] = x;
			auto tempIt = maxPopulation.find(-1 * temp);
			maxPopulation.erase(tempIt);
			maxPopulation.insert(-1 * x);
			queries.push_back(make_tuple('P', second, temp));
		} else if (c == 'D') {
			auto tempIt = roads.find(second);
			pair<long long, long long> road = tempIt->second;
			queries.push_back(make_tuple('D', road.first, road.second));
			roads.erase(second);
		} else {
			printf("Something is wrong\n");
			printf("%c\n", c);
			return 1;
		}
	}

	// for (int i = 1; i <= n; i++) {
	// 	printf("%lld ", population[i]);
	// }
	// printf("\n");

	// for (auto it = roads.begin(); it != roads.end(); it++) {
	// 	printf("%d ", it->first);
	// 	pair<int, int> other = it->second;
	// 	printf("%d %d\n", other.first, other.second);
	// 	// cout<<other.first<<' '<<other.second<<' ';
	// }

	// for (auto it = queries.begin(); it != queries.end(); it++) {
	// 	tuple<char, int, long long> temp = *it;
	// 	printf("%c %d %lld\n", get<0>(temp), get<1>(temp), get<2>(temp));

	// }

	for (auto it = roads.begin(); it != roads.end(); it++) {
		pair<long long, long long> road = it->second;
		join((road.first), (road.second));
	}
	auto finalMax = maxPopulation.lower_bound(-50000000000);
	output.push_back(-1*(*finalMax));
	//cout<<-1* (*finalMax)<<'\n';

	for (auto it = queries.rbegin(); it != queries.rend() - 1; it++) {
		tuple<char, long long, long long> temp = *it;
		if (get<0>(temp) == 'P') {
			long long city = get<1>(temp);
			long long pop = get<2>(temp);
			long long rootNode = root(city);
			long long previousPopulation = secondPopulation[city];
			secondPopulation[city] = pop;
			long long currentPopulationRegion = population[rootNode];
			population[rootNode] = currentPopulationRegion + (pop - previousPopulation);
			auto popIt = maxPopulation.find(-1*currentPopulationRegion);
			maxPopulation.erase(popIt);
			maxPopulation.insert(-1 * (currentPopulationRegion + (pop - previousPopulation)));
		} else {
			pair<long long, long long> road = make_pair(get<1>(temp), get<2>(temp));
			join((road.first), (road.second));
		}
		auto finalMax = maxPopulation.lower_bound(-50000000000);
		output.push_back(-1*(*finalMax));

	}

	for (auto it = output.rbegin(); it != output.rend(); it++) {
		cout<<*it<<'\n';
	}


	return 0;
}