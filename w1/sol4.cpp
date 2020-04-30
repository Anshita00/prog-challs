#include <iostream>
#include<cstring>
#include <sstream>
#include <queue> 

using namespace std;
int minMoves = 9;

bool canPlace(int rowPosition, int columnPosition, int curPositions[8]) {

	for (int i = 0; i < columnPosition; i++) {
		if (curPositions[i] == rowPosition) {
			return false;
		}
		if ((curPositions[i] - i) == (rowPosition - columnPosition)) {
			return false;
		}
		if ((curPositions[i] + i) == (rowPosition + columnPosition)) {
			return false;
		}
	}

	return true;
}

void placeQueens (int positions[8], int curIndex, int curMoves, int curPositions[8]) {

	if (curIndex == 8) {
		// cout<<"Curmoves in the base case"<<curMoves<<' '<<"Minmoves"<<minMoves<<endl;
		if (curMoves < minMoves) {
			minMoves = curMoves;
		}
		// cout<<"Printing curPositions in final base step"<<endl;
		// for (int i = 0; i < 8; i++) {
		// 	cout<<curPositions[i]<<' ';
		// }
		// cout<<endl;
		return;
	}

	int curPositionsCopy[8];

	for (int i = 0; i < 8; i++) {
		int curMovesTemp = curMoves;
		for (int i = 0; i < 8; i++) {
			curPositionsCopy[i] = curPositions[i];
		}
		if (!canPlace(i, curIndex, curPositions)) {
			// cout<<"Can't place"<<i<<' '<<curIndex<<endl;
			// cout<<"Printing curPositions"<<endl;
			// for (int i = 0; i < 8; i++) {
			// 	cout<<curPositions[i]<<' ';
			// }
			// cout<<endl;
			continue;
		}
		if (positions[curIndex] != i) {
			curMovesTemp++;
			// cout<<"Incrementing curMoves "<<curMovesTemp<<endl;
		}
		curPositionsCopy[curIndex] = i;
		// cout<<"CurMoves "<<curMoves<<endl;
		// cout<<"CurMovesTemp "<<curMovesTemp<<endl;
		// for (int i = 0; i < 8; i++) {
		// 	cout<<positions[i]<<' ';
		// }
		// cout<<endl;
		placeQueens(positions, curIndex + 1, curMovesTemp, curPositionsCopy);
	}
}

int main()
{
 
    string line;
    int numCase = 1;

    while (getline(cin, line)) {
    	minMoves = 9;
		int positions[8];
        istringstream iss;
        iss.str(line);

        for (int i = 0; i < 8; i++) {
        	int temp;
        	iss >> temp;
        	positions[i] = temp - 1;
        }

        // cout<<line<<endl;;
        // for (int i = 0; i< 8; i++) {
        // 	cout<<positions[i]<<' ';
        // }
        // cout<<endl;
        int curPositions[8];
        for (int i = 0; i < 8; i++) {
        	curPositions[i] = positions[i];
        }
        placeQueens(positions, 0, 0, curPositions);
        cout<<"Case "<<numCase<<": "<<minMoves<<endl;
        numCase++;
        // for (int i = 0; i < 8; i++) {
        // 	cout<<curPositions[i]<<' ';
        // }
        // cout<<endl;
    }

}