#include <iostream>
#include<cstring>
#include <sstream>
#include <queue> 

using namespace std;


int main()
{
	string line;
 	bool openingFound = false;

 	while (getline(cin, line)) {
	    istringstream iss;
	    iss.str(line);
	    string output;

	    for (auto it = line.cbegin(); it != line.cend(); ++it) {
	    	//cout<<*it<<' ';
	    	char cur = *it;
	    	if (cur != '"') {
	    		output.push_back(cur);
	    	} else {
	    		if (openingFound) {
	    			output.push_back('\'');
	    			output.push_back('\'');
	    			openingFound = false;
	    		} else {
	    			output.push_back('`');
	    			output.push_back('`');
	    			openingFound = true;
	    		}
	    	}
	    }
	    cout<<output<<endl;
 	}

}
