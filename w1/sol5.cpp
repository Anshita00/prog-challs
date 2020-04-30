#include <iostream>
#include<cstring>
#include <sstream>
#include <queue> 

using namespace std;
vector<int> cars;


void findEarliestTime(int n, int t, int m) {

	int totalTrips = (m + n - 1) / n;
	int minTime = 0;
	t = t + t;

	for (int i = (m + n - 1) % n; i < m; i+= n) {
		if (minTime > cars.at(i)) {
			minTime = minTime + t;
		} else {
			minTime = cars.at(i) + t;
		}
	}

	cout<<minTime - t/2<<' '<<totalTrips<<endl;

	// int curTrips = 0;
	// int curTime = 0;
	// int curCarTime = 0;
	// int carsLeft = 0;
	// int nextCarTime = 0;

 //    for (int i = 0; i < m - n; i++) {
	//     // cout<<"Reached here"<<endl;
	//     // cout<<"Cur time "<<curTime<<"Num trips "<<curTrips<<endl;
 //    	curCarTime = cars.at(i);
 //    	// if (it == cars.begin()) {
 //    	// 	curTime = curCarTime;
 //    	// }
 //    	nextCarTime = cars.at(i+1);

 //    	// cout<<"Cur car time"<<curCarTime<<endl;
 //    	carsLeft++;

 //    	if (carsLeft < n) {
 //    		if (curCarTime + t + t <= nextCarTime && curCarTime >= curTime) {
 //    			curTrips++;
 //    			carsLeft = 0;
 //    			curTime = nextCarTime;
 //    		} else if (i == (m - n- 1 )&& curCarTime >= curTime) {
 //    			curTrips++;
 //    			carsLeft = 0;
 //    			curTime = curCarTime + t + t;
 //    		}
 //    	} else {
 //    		curTrips++;
 //    		curTime = curCarTime + t + t;
 //    		carsLeft -= n;
 //    	}
 //    }

 //    curTrips++;
 //    int lastTime = cars.at(m - 1);
 //    if (lastTime > curTime) {
 //    	curTime = lastTime;
 //    }
 //    curTime = curTime + t;

 //    cout<<curTime<<' '<<curTrips<<endl;
}


int main()
{
 
    int numTestCases;
    cin>>numTestCases;

    for (int i = 0; i < numTestCases; i++) {
    	cars.clear();
    	int n, t, m;
        cin>>n>>t>>m;

        int temp;
        for (int j = 0; j < m; j++) {
        	cin>>temp;
        	cars.push_back(temp);
        }

        findEarliestTime(n,t,m);


    }

}