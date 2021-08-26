#include "pente.h"
using namespace std;

int score_black = 0; //Each piece captured adds +1 to score
int score_white = 0;
const int WIN_THRESHOLD = 10; //You win if you capture 10 pieces

//Uppercases a string
void uppercaseify(std::string &s) {
	for (char &c : s) c = toupper(c);
}

//Quits the program with an error message
void die(const std::string &error = "INVALID INPUT!") {
	std::cout << error << std::endl;
	exit(EXIT_FAILURE);
}

//Return true if the current move (x,y) results in five in a row (or more)
// in a horizontal, vertical, or diagonal direction.
//Remember to BOUNDS CHECK - never go off the edge of the vector
//It takes the state of the board, and the x and y coordinates of the last move
bool check_for_win(const vector<vector<char>> &board, const int x, const int y) {
	//YOU
	int horiz = 1, vert = 1, diag_1= 1, diag_2 = 1; //counter for each direction of possible win
	const int WIN_NUM = 5;
	const int RIGHT = 0, DOWN = 1, DOWN_RIGHT = 2, DOWN_LEFT = 3, LEFT = 4, UP = 5, UP_LEFT = 6, UP_RIGHT = 7;//unit vector directions 
	int y_change = 0;
	int x_change = 0;
	
	for (size_t j = 0; j < moves8.size(); j++) { //access unit direction vector {u,v} from move4 vector in header file
		
		y_change = moves8[j].first; // made variables to use for unit vector change on each iteration
		x_change = moves8[j].second;
		
		for (int i = 1; i < WIN_NUM; i++) {      //for each unit vec, continue in that direction for same color piece
			
			if ((y + i * y_change) >=  SIZE || (x + i * x_change) >= SIZE) break; //break if spot is bigger than size of array
			if ((y + i * y_change) < 0 || (x + i * x_change) < 0) break; //break if spot is smaller than size of array
			
			//if statement below checks that new spot is equal to previous spot
			if (board[y + i * y_change][x + i * x_change] == board[y + (i-1) * y_change][x + (i-1) * x_change]) { 
				//add to correct directional counter given which unit vector is being used in current iteration
				if (j == RIGHT || j == LEFT) horiz++;
				if (j == DOWN || j == UP) vert++;
				if (j == DOWN_RIGHT || j == UP_LEFT) diag_1++;
				if (j == DOWN_LEFT || j == UP_RIGHT) diag_2++;
			}
			else break; //break if adjacent spot isn't same color
		}
	}
	//if at least 5 in a row, return true
	if (horiz >= 5 || vert >= 5 || diag_1 >= 5 || diag_2 >= 5) 
		return true;
	else
	return false; //if there isn't five in a row, return false 
}

//This function looks to see if a capture has been made, and makes it if so.
//A capture is when the new piece flanks exactly two opposing pieces with one of the same color
//For example, if you have _BBW, and white moves into the blank: WBBW, this is a capture.
// It turns into W__W, and white gets +2 added to its score. (All captures add +2 to score.)
//You win if one side gets 10 points.
//It takes the state of the board, and the x and y coordinates of the last move
void capture(vector<vector<char>> &board, const int x, const int y) {
	//YOU
	const int ENDSPOT = 4;
	char curr_spot = board[y][x];//character of last move on board
	int y_change = 0;
	int x_change = 0;
	int x_1 = 0, x_2 = 0, x_3 = 0;
	int y_1 = 0, y_2 = 0, y_3 = 0;
	
	for (size_t j = 0; j < moves8.size(); j++) { //iterate over pair vectors in moves8 vector
		y_change = moves8[j].first; 
		x_change = moves8[j].second;
		//Bound check and check none of spots are open
		for (int i = 1; i < ENDSPOT; i++) {
			
			//Check for bounds and that no spots in checked spots are open
			if ((y + i * y_change) >=  SIZE || (x + i * x_change) >= SIZE) break; //break if spot is bigger than size of array
			if ((y + i * y_change) < 0 || (x + i * x_change) < 0) break; //break if spot is smaller than size of array
			if (board[y + i * y_change][x + i * x_change] == OPEN) break; //break if one of spots to be checked is open
			
			if (i == ENDSPOT - 1) { //only run this conditional at end of loop so it only runs once
				
				y_1 = y + y_change, y_2 = y + 2 * y_change, y_3 = y + 3 * y_change; //initialize shorthands for positions checked
				x_1 = x + x_change, x_2 = x + 2 * x_change, x_3 = x + 3 * x_change;
				
				// conditional below checks that curr_spot makes a capture
				if ((curr_spot == board[y_3][x_3]) && (board[y_1][x_1] == board[y_2][x_2]) && (curr_spot != board[y_1][x_1])) {
					board[y_1][x_1] = OPEN;
					board[y_2][x_2] = OPEN;
					
					if (curr_spot == WHITE) score_white += 2;
					else if (curr_spot == BLACK) score_black += 2;
				}
			}
		}
	} 
}

//Return true iff every square is not OPEN
bool check_for_draw(const vector<vector<char>> &board) {
	//YOU
	for (int row = 0; row < SIZE; row++) {
		for (int col = 0; col < SIZE; col++) {
			if (board.at(row).at(col) == OPEN) 
				return false;
		}
	}
	return true; 
}

void print_board(const vector<vector<char>> &board, const bool black) {
	cout << '';
	cout << "CURRENT TURN: " << (black ? "BLACK\n" : "WHITE\n");
	cout << "SCOREBOARD - WHITE: " << score_white << " BLACK: " << score_black << endl << endl;
	//Column headers
	cout << "  ";
	for (int col = 0; col < SIZE; col++)
		cout << col / 10;
	cout << endl;
	cout << "  ";
	for (int col = 0; col < SIZE; col++)
		cout << col % 10;
	cout << endl;
	for (int row = 0; row < SIZE; row++) {
		cout << setw(2) << row; //Print row headers
		for (int col = 0; col < SIZE; col++) {
			//cout << "row: " << row << " col: " << col << " is: ";
			cout << board.at(row).at(col);
		}
		cout << endl;
	
	}
}

//YOU: If you want extra credit, write these functions in ai1.cc and ai2.cc
void ai1_move(const vector<vector<char>> &board, int &x, int &y);
void ai2_move(const vector<vector<char>> &board, int &x, int &y);

//Takes a board state in by const reference, returns into x and y the
// coordinates the human player wants to make
void human_move(const vector<vector<char>> &board, int &x, int &y) {
	bool first_try = true;
	while (true) {
		if (!first_try) cout << "Invalid move, try again.\n";
		first_try = false;
		cout << "Please enter a move (x y):\n";
		cin >> x >> y;
		if (!cin) { //Bad move, redo
			cin.clear(); //Clear error flag
			string temp;
			getline(cin, temp); //Pull offending string out of cin
			continue;
		}
		if (x < 0 || x >= SIZE || y < 0 || y >= SIZE) //Bad move, redo
			continue;
		if (board[y][x] != OPEN)  //Bad move, redo
			continue;
		//Ok, x and y have been set, return
		return;
	}
}

//Sets the board back to factory defaults
void reset_board(vector<vector<char>> &board) {
	for (int i = 0; i < SIZE; i++) {
		board.at(i).resize(0); //Clear existing row
		board.at(i).resize(SIZE, OPEN); //Set row to all OPEN spaces
	}
	board[SIZE / 2][SIZE / 2] = WHITE; //Starting move is always white in the middle
}

//Ends the game
void win(const vector<vector<char>> &board, bool won, bool black = true, string reason = "") {
	print_board(board,black);
	if (!won) {
		cout << "DRAW!\n";
		exit(EXIT_SUCCESS);
	}
	if (reason != "") 
		cout << reason << endl;
	cout << (black ? "BLACK" : "WHITE") << ", A WINNER IS YOU!\n";
	exit(EXIT_SUCCESS);
}

int main() {
	//Part 1 - Set up the board
	vector<vector<char>> board(SIZE); //19x0 until resized by reset_board
	reset_board(board);

	/* -----------------------------------------------------------------*/

	//Part 2 - Set up the Pseudorandom Number Generator (PNG)
	cout << "Enter random seed:\n"; //This gives deterministic AI behavior
	int seed = 0;
	cin >> seed;
	srand(seed);

	/* -----------------------------------------------------------------*/

	//Part 3 - Set up the players in the game
	//p1 and p2 are variables holding functions!! They get called to make a move for white / black
	//ai1 is a white player AI, ai2 is a black player AI
	auto p1 = ai1_move; //Set player 1 under AI control
	auto p2 = ai2_move; //Set player 2 under AI control

	cout << "How many human players? (Type \"0\", \"1\", or \"2\")\n";
	int players = 0;
	cin >> players;
	if (!cin || players < 0 || players > 2) die("Bad # of Players");
	if (players == 2) {
		p1 = human_move; //Set player 1 under human control
		p2 = human_move; //Set player 2 under human control
	}
	else if (players == 1) {
		while (true) {
			cout << "Do you want to be the white or black player? (Type \"white\" or \"black\")\n";
			string s;
			cin >> s;
			uppercaseify(s);
			if (s == "WHITE") {
				p1 = human_move; //Set player 1 under human control
				break;
			} else if (s == "BLACK") {
				p2 = human_move; //Set player 2 under human control
				break;
			}
		}
	}

	/* -----------------------------------------------------------------*/

	//Part 4 - Main loop
	bool black = true; //Black goes first, since white starts with a free move
	while (true) {
		//usleep(200000); //Small delay
		int x = 0, y = 0; //Holds the move returned by p1 and p2
		print_board(board, black);
		if (black)
			p2(board, x, y); //Returns x and y by reference
		else
			p1(board, x, y); //Returns x and y by reference
		//Sanity check the move returned by the player or AI
		if (x < 0 || x >= SIZE || y < 0 || y >= SIZE || board[y][x] != OPEN)
			win(board,true,!black,"INVALID MOVE!");

		//Make the move
		board[y][x] = (black ? BLACK : WHITE);

		//Check for capture
		capture(board, x, y);

		//Check for win by score after capture
		if (score_black >= WIN_THRESHOLD || score_white >= WIN_THRESHOLD)
			win(board,true,black,"WIN BY CAPTURE!");

		//Check for win by 5 in a row (or more)
		if (check_for_win(board, x, y))
			win(board,true,black,"WIN BY 5+ IN A ROW!");

		//Check for draw
		if (check_for_draw(board))
			win(board,false); //Draw

		//Change whose turn it is
		black = !black;
	}
}
