#include <iostream>
#include<cstring>
#include <sstream>
#include <queue> 
#include <tuple>
#include <bits/stdc++.h>
#include <set>

using namespace std;

bool compareInterval(tuple<int, int> first, tuple<int, int> second) {
	int firstEndTime = get<1>(first);
	int secondEndTime = get<1>(second);
	int firstStartTime = get<0>(first);
	int secondStartTime = get<0>(second);
	if (firstEndTime == secondEndTime) {
		return firstStartTime < secondStartTime;
	}
	return firstEndTime < secondEndTime;
}

int main()
{
	int k, n;
	vector<tuple<int, int>> times;
	multimap<int, int> classrooms;

	scanf("%d %d", &n, &k);

	for (int i = 0; i < n; i++) {
		int s, f;
		scanf("%d %d", &s, &f);
		times.push_back(make_tuple(s, f));
	}

	if (k >= n) {
		printf("%d\n", n);
		return 0;
	}


	sort(times.begin(), times.end(), compareInterval);
	classrooms.clear();

	int numAssigned = 0;
	for (int i = 0; i < n; i++) {
		auto classroom = classrooms.upper_bound(-1 * (get<0>(times.at(i))));
		if (classroom == classrooms.end()) {
			int size = classrooms.size();
			if (size < k) {
				classrooms.insert(pair<int,int>(-1* (get<1>(times.at(i))), size + 1));
				numAssigned++;
			}
			continue;
		} else {
			int index = classroom->second;
			classrooms.erase(classroom);
			classrooms.insert(pair<int,int>(-1* (get<1>(times.at(i))), index));
			numAssigned++;
		}



		// for (int j = 0; j < k; j++) {
		// 	if (classrooms[j] != -1) {
		// 		tuple<int, int> temp = times.at(classrooms[j]);
		// 		if (get<1>(temp) < get<0>(times.at(i))) {
		// 			classrooms[j] = i;
		// 			numAssigned++;
		// 			break;
		// 		}
		// 	} else {
		// 		classrooms[j] = i;
		// 		numAssigned++;
		// 		break;
		// 	}
		// }
	}

	cout<<numAssigned<<endl;

	return 0;
}