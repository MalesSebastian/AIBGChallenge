#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "utility.hpp"

int distance(int x1, int y1, int x2, int y2) {
    return std::max(abs(x1 - x2), abs(y1 - y2));
}

bool friendlyWithinDistance(const State& st, int r, int s) {
    int d = st.maxColonisationDistance;
    for (int i = r - d; i <= r + d; ++i)
        for (int j = s - d; j <= s + d; ++j) {
            if (st.isMineCell(i, j) && distance(i, j, r, s) <= d)
                return true;
    }
    return false;
}

std::vector<std::pair<int, int> > dummyActions (const State& st) {

  std::vector<std::pair<int, int> > possibleMoves;
  for (int i = 0; i < st.rows; i++) {
      for (int j = 0; j < st.cols; j++) {
          if (st.isEmptyCell(i, j) && friendlyWithinDistance(st, i, j))
              possibleMoves.push_back(std::make_pair(i, j));
      }
  }
  return possibleMoves;
}

int main() {
    for( std::string line; getline( std::cin, line );){
        auto state = State(line);
     	
	int counter  = 0;
	std::vector <std::pair<int, int> > moves; 

	for(int i = 0; i < state.rows; i++){
		for(int j = 0; j < state.cols; j++){
			if( state.isMineCell(i,j) && state.inField(i - 1 , j - 1) && state.field[i - 1][j - 1] != '#'  && (counter < state.cellGainPerTurn) ){
			    moves.push_back(std::make_pair(i - 1, j - 1));
			    counter++;
			}
		}
	}

	state.commitAction(std::cout, moves);
    }

}
