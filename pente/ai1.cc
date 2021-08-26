#include "pente.h"
using namespace std;

//WHITE AI
//Takes a board state in by const reference, returns into x and y the
// coordinates the player wants to make
//Default AI is terribad - just picks a random open spot
void ai1_move(const vector<vector<char>> &board, int &x, int &y) {
	vector<pair<int, int>> open; //List of all open spots

	//Scan through whole board for all open spots and add to vector
	for (int row = 0; row < SIZE; row++)
		for (int col = 0; col < SIZE; col++)
			if (board[row][col] == OPEN)
				open.push_back({row, col}); //Inserting a pair of ints using {} notation

	if (open.size() == 0) die("ERROR: No open spots, this should have been a draw.");

	const int END_SPOT_4 = 5;
	int y_change = 0;
	int x_change = 0;
	bool is_3 = false;
	bool is_2 = false;
	bool is_1 = false;
	int temp_3_y = 0, temp_3_x = 0; //temp variables that will be used if loop finds 3 in a row  
	int temp_2_y = 0, temp_2_x = 0; // temp for 2 in row
	int temp_1_y = 0, temp_1_x = 0;	// temp for just 1 piece found
//FOR WHITE AI TO WIN 
for (int row = 0; row < SIZE; row++) {
		for (int col = 0; col < SIZE; col++) {
			
			if (board[row][col] == OPEN) {
				//TRY FOR WIN
				for (size_t j = 0; j < moves8.size(); j++) {
					y_change = moves8[j].first;
					x_change = moves8[j].second;

					for (int i = 1; i < END_SPOT_4; i++) {
						if ((row + i * y_change) >= SIZE || (col + i * x_change) >= SIZE) break;
						if ((row + i * y_change) < 0 || (col + i * x_change) < 0) break;
						//conditional will break if current "i" doesn't give same color
						//but it will store spot in case best spot on board is 4 in row, 3 in row, etc.
						if (board[row + i * y_change][col + i * x_change] != WHITE) { 
							
							
							//special case win spot that could lead to 5 eg W_WWW
							if ( (i == 4 && board[row + (i-1) *y_change][col + (i-1) * x_change] == WHITE && (row - y_change) < SIZE && (col - x_change) < SIZE
							&& (row - y_change) >= 0 && (col - x_change) >= 0 && board[row - y_change][col - x_change] == WHITE) || 
							 (i == 2 && board[row + (i-1) *y_change][col + (i-1) * x_change] == WHITE && (row - y_change) < SIZE && (col - x_change) < SIZE
							&& (row - y_change) >= 0 && (col - x_change) >= 0 && board[row - y_change][col - x_change] == WHITE && 
							(row - 2 * y_change) < SIZE && (col - 2 * x_change) < SIZE && (row - 2 * y_change) >= 0 && (col -2 * x_change) >= 0 
							&& board[row - 2 * y_change][col - 2 * x_change] == WHITE && (row - 3 * y_change) < SIZE && (col - 3 * x_change) < SIZE 
							 && (row - 3 * y_change) >= 0 && (col - 3 * x_change) >= 0 && board[row - 3 * y_change][col - 3 * x_change] == WHITE)) {
								y = row;
								x = col;
								return;
							}
							//special case of win spot that could lead to 5 eg WW_WW
							if ( i == 3 && board[row + (i-1) *y_change][col + (i-1) * x_change] == WHITE && (row - y_change) < SIZE && (col - x_change) < SIZE
							&& (row - y_change) >= 0 && (col - x_change) >= 0 && board[row - y_change][col - x_change] == WHITE && 
							(row - 2 * y_change) < SIZE && (col - 2 * x_change) < SIZE && (row - 2 * y_change) >= 0 && (col -2 * x_change) >= 0 
							&& board[row - 2 * y_change][col - 2 * x_change] == WHITE) {
								y = row;
								x = col;
								return;
							}
							//run this conditional if loop found 3 of same in a row. 
							if (i == END_SPOT_4 - 1 && !is_3) { // don't run through again once 3 in row found
							
								//break if deadend. e.g current open spot looks like B_WWWB
								if(board[row + i *y_change][col + i * x_change] == BLACK && (row - y_change) < SIZE && (col - x_change) < SIZE
									&& (row - y_change) >= 0 && (col - x_change) >= 0 && board[row - y_change][col - x_change] == BLACK) break;
								is_3 = true; //set this to true to mark spot where there is 3 in a row for later use
								temp_3_y = row;
								temp_3_x = col; 
								break;
							}
							else if (i == END_SPOT_4 - 2 && !is_2) { //don't run through once 2 in row found
								
								is_2 = true;
								temp_2_y = row;
								temp_2_x = col;
								break;
							}
							else if (i == END_SPOT_4 - 3 && !is_1) { //don't run through again once 1 of same color found
								//conditional below is to make sure ai doesn't walk into a capture
								//checks one more spot over before running to make sure spot over isn't opposite color
								
								if (board[row + i * y_change][col + i * x_change] == BLACK) break;
								is_1 = true;
								temp_1_y = row;
								temp_1_x = col;
								break;
							}
							else break;
						}
						//ai sees 4 of same color in a row after open spot
						if (i == END_SPOT_4 - 1) {
							y = row; 
							x = col; 
							return;
						}
					}
				}
			}
		}
	} //End of ai win code

// BLOCK CODE	
	bool is_block_3 = false;
	bool is_block_2 = false;
	bool special_is_block_3 = false;
	int special_block_3_y = 0, special_block_3_x = 0;
	int block_3_y = 0, block_3_x = 0;
	int block_2_y = 0, block_2_x = 0;
    //FOR WHITE TO BLOCK 	
	for (int row = 0; row < SIZE; row++) {
		for (int col = 0; col < SIZE; col++) {
			
			if (board[row][col] == OPEN) {
				//TRY FOR BLOCK
				for (size_t j = 0; j < moves8.size(); j++) {
					y_change = moves8[j].first;
					x_change = moves8[j].second;

					for (int i = 1; i < END_SPOT_4; i++) {
						if ((row + i * y_change) >= SIZE || (col + i * x_change) >= SIZE) break;
						if ((row + i * y_change) < 0 || (col + i * x_change) < 0) break;
						
						if (board[row + i * y_change][col + i * x_change] != BLACK) { 
							
							//special case blocking spot that could lead to 5 eg B_BBB
							if ( (i == 4 && board[row + (i-1) *y_change][col + (i-1) * x_change] == BLACK && (row - y_change) < SIZE && (col - x_change) < SIZE
							&& (row - y_change) >= 0 && (col - x_change) >= 0 && board[row - y_change][col - x_change] == BLACK) || 
							 (i == 2 && board[row + (i-1) *y_change][col + (i-1) * x_change] == BLACK && (row - y_change) < SIZE && (col - x_change) < SIZE
							&& (row - y_change) >= 0 && (col - x_change) >= 0 && board[row - y_change][col - x_change] == BLACK && 
							(row - 2 * y_change) < SIZE && (col - 2 * x_change) < SIZE && (row - 2 * y_change) >= 0 && (col -2 * x_change) >= 0 
							&& board[row - 2 * y_change][col - 2 * x_change] == BLACK && (row - 3 * y_change) < SIZE && (col - 3 * x_change) < SIZE 
							 && (row - 3 * y_change) >= 0 && (col - 3 * x_change) >= 0 && board[row - 3 * y_change][col - 3 * x_change] == BLACK)) {
								y = row;
								x = col;
								return;
							}
							//special case of blocking middle spot that could lead to 5 eg BB_BB
							if ( i == 3 && board[row + (i-1) *y_change][col + (i-1) * x_change] == BLACK && (row - y_change) < SIZE && (col - x_change) < SIZE
							&& (row - y_change) >= 0 && (col - x_change) >= 0 && board[row - y_change][col - x_change] == BLACK && 
							(row - 2 * y_change) < SIZE && (col - 2 * x_change) < SIZE && (row - 2 * y_change) >= 0 && (col -2 * x_change) >= 0 
							&& board[row - 2 * y_change][col - 2 * x_change] == BLACK) {
								y = row;
								x = col;
								return;
							}

							// run this loop if spot looks like _BBB_
							if (i == END_SPOT_4 - 1 && !special_is_block_3 && board[row + i * y_change][col + i * x_change] == OPEN) {
								//special case where it sees 3 in row of opp color and other side is open so that opp can grow from either direction
								special_is_block_3 = true;
								special_block_3_y = row;
								special_block_3_x = col;
								break;
							}
							//run this conditional if loop found 3 of same in a row. 
							if (i == END_SPOT_4 - 1 && !is_block_3) { // don't run through again once 3 in row found
								//ai saw only 3 in a row of opposite color
								is_block_3 = true; //set this to true to mark spot where there is 3 in a row for later use
								block_3_y = row;
								block_3_x = col; 
								break;
							}
							if (i == END_SPOT_4 - 2 && !is_block_2) { //don't run through once 2 in row found
								//ai saw only 2 in a row of opposite color
								is_block_2 = true;
								block_2_y = row;
								block_2_x = col;
								break;
							}
							else break;
						}
						//ai sees 4 of same color in a row after open spot
						if (i == END_SPOT_4 - 1) {
							y = row; 
							x = col; 
							return;
						}
					}
				}
			}
		}
	} //End of ai block code
	

// CAPTURE CODE
	const int END_SPOT_3 = 4;
	int x_1 = 0, x_2 = 0, x_3 = 0;
	int y_1 = 0, y_2 = 0, y_3 = 0;

	for (int row = 0; row < SIZE; row++) {
		for (int col = 0; col < SIZE; col++) {
			
			//make sure spot is open before continuing
			if (board[row][col] == OPEN) {
				
				//iterate over every direction
				for (size_t j = 0; j < moves8.size(); j++) {
					y_change = moves8[j].first;
					x_change = moves8[j].second;
					
					//iterate over 3 spots over from current location
					for (int i = 1; i < END_SPOT_3; i++) {
						//bounds checks
						if ((row + i * y_change) >= SIZE || (col + i * x_change) >= SIZE) break;
						if ((row + i * y_change) < 0 || (col + i * x_change) < 0) break;
						if (board[row + i * y_change][col + i * x_change] == OPEN) break;
						
						//if bounds checks met
						if (i == END_SPOT_3 - 1) {
							y_1 = row + y_change, y_2 = row + 2 * y_change, y_3 = row + 3 * y_change;
							x_1 = col + x_change, x_2 = col + 2 * x_change, x_3 = col + 3 * x_change;
							
							//check that move would capture
							if ((board[y_3][x_3] == WHITE)  && (board[y_1][x_1] == board[y_2][x_2]) && (board[y_1][x_1] == BLACK)) {
								y = row;
								x = col;
								return;
							}
						}
					}
				}
			}
		}
	}
//play for 4 in a row	
	if (is_3) {
		y = temp_3_y;
		x = temp_3_x;
		return;
	}

// special block 3 in a row of opp color when there are openings on both sides WBBB_
	if (special_is_block_3) {
		y = special_block_3_y;
		x = special_block_3_x;
		return;
	}
// play for 3 in a row
	if (is_2) {
		y = temp_2_y;
		x = temp_2_x;
		return;
	}

// to block 3 in a row of opposite color eg WBBB
	if (is_block_3) {
		y = block_3_y;
		x = block_3_x;
		return;
	}
// play for 2 in a row
	if (is_1) {
		y = temp_1_y;
		x = temp_1_x;
		return;
	}
// to block 2 in a row of opposite color eg WBB
	if (is_block_2) {
		y = block_2_y;
		x = block_2_x;
		return;
	}	
// pick random spot to play at
	size_t pick = rand() % open.size(); //Pick a random open spot
	y = open.at(pick).first; //y means row
	x = open.at(pick).second; //x means column
	
}

