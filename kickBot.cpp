#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "utility.hpp"

int dx[] = {0, 0, 1, -1, 1, 1, -1, -1};
int dy[] = {1, -1, 0, 0, 1, -1, -1, 1};

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

bool placeable(State state, int x, int y){
  int neib = 0, newX, newY;
  for(int i = 0; i < 8; ++i){
    newX = x + dx[i];
    newY = y + dy[i];
    if(state.isMineCell(newX, newY))
        neib++;
  }
  return neib <= 3 && neib >= 2;
}


std::vector <std::pair<int, int> > random(State state){
	std::vector <std::pair<int, int> > moves;
  bool ok = true;
  int count_friendly = 0, nr;
  for(int i = 0; i < state.rows; ++i){
    for(int j = 0; j < state.cols; ++j)
      if(state.isMineCell(i, j))
          count_friendly++;
  }
  while(ok){
    nr = rand() % 10;
    if(nr <= count_friendly){
      ok = false;
      break; 
    }
  }
  count_friendly = 0;
  for(int i = 0; i < state.rows; ++i){
    for(int j = 0; j < state.cols; ++j){
      if(state.isMineCell(i, j) && count_friendly < nr)
        count_friendly++;
      else if(state.isMineCell(i, j) && count_friendly >= nr && count_friendly - nr < state.cellsRemaining)
        ok = true;
        int direction = rand() % 8;
        if(placeable(state, i + dx[direction], j + dy[direction])){
          count_friendly++; 
          moves.push_back(std::make_pair(i + dx[direction], j + dy[direction]));
        }
      }
    }
  return moves;
}


std::vector <std::pair<int, int> >arrange_items(State state, int x, int y){
	std::vector <std::pair<int, int> > moves;
  int side = 1;
	for(int i = 0; i < state.rows; i++){
		for(int j = 0; j < state.cols; j++){
			switch (side){
				case 1:
					if( state.isMineCell(i, j) && state.isEmptyCell(i-1, j) ){
						moves.push_back(std::make_pair(x,y));
						side++;
					}
					break;
				case 2:
					if( state.isMineCell(i, j) && state.isEmptyCell(i, j+1) ){
						moves.push_back(std::make_pair(x,y));
						side++;
					}
					break;
				case 3:
					if( state.isMineCell(i, j) && state.isEmptyCell(i+1, j) ){
						moves.push_back(std::make_pair(x,y));
						side++;
					}
					break;
				case 4: 
					if( state.isMineCell(i, j) && state.isEmptyCell(i, j-1) ){
						moves.push_back(std::make_pair(x,y));
						side = 1;
					}
					break;
			}
		}
	}
  return moves;
}

int main() {
  for(std::string line; getline( std::cin, line );){
    auto state = State(line);
	  int counter = 0;
    if(state.cellGainPerTurn < 3)
      auto response = random(state);
    else
      auto response = arrange_items(state);
	  state.commitAction(std::cout, moves);
  }
}
