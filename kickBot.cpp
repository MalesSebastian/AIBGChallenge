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

void get_line(int x, int y, std::pair<int, int>square_init){
	if( isEmptyCell(x-1, y) ){
		if( isEmptyCell(x-1, y-1) && isEmptyCell(x-1, y+1) ){
			square.first=x-1;
			square.second=y-1;
		    	moves.push_back(std::make_pair( x-1, y-1 ) );
			moves.push_back(std::make_pair( x-1, y ) );
			moves.push_back(std::make_pair( x-1, y+1 ) );
		}
		else{
			moves.push_back(std::make_pair( x-1, y ) );
			/// RANDOM
		}
	}
}

void get_square(int x, int y){
	if(isEmptyCell(x, y-1) && isEmptyCell(x-1, y) && isEmptyCell(x-1, y-1) ){
		moves.push_back(std::make_pair( x, y-1 ) );
		moves.push_back(std::make_pair( x-1, y ) );
		moves.push_back(std::make_pair( x-1, y-1 ) );
	}
	else{
		/// RANDOM
	}
}

bool flag = true;

std::vector <std::pair<int, int> >arrange_items(State state){
	std::vector <std::pair<int, int> > moves;
	for(int i = 0; i < state.rows; i++){
		for(int j = 0; j < state.cols; j++){
			if( isMineCell(i, j) ){
				if(flag){
					std::pair<int, int> square_init;
					get_line(i, j);
					flag = false;
				}	
				else{
					
				}
			}				
		}
	}
  return moves;
}

int main() {
  for(std::string line; getline( std::cin, line );){
    auto state = State(line);
    std::vector <std::pair<int, int> >response;
    int counter = 0;
    if(state.cellGainPerTurn < 3)
      response = random(state);
    else
      response = arrange_items(state);
    
    state.commitAction(std::cout, response);
  }
}
