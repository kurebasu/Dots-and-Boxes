/*
*File: main.cc
*Author: Said Krebbers (s1381164)
*Last edit date: -
*/

static const int UP = 0;
static const int RIGHT = 1;
static const int DOWN = 2;
static const int LEFT = 3;

class Dotsboxes{
public:
	Dotsboxes(); 										//Constructor
	Dotsboxes(int w, int h);							//Constructor
	// ~Dotsboxes(); 									//Destructor
	static const int maxSize = 8;						//maximum dimentions of the board (in boxes)
	static const int minSize = 1;						//minimum size of the board (in boxes)

	int getHeight(){return height;}
	int getWidth(){return width;}
	void getWinner(int &result, double &ratio);
	void getWinnerMC(int &result, double &ratio);


	void print();										//prints the board
	void cleanBoard();									//empties the board
	bool whois();										//returns whose turn it is (false = player 1, true = player 2)
	void changeTurn();
	int numberOfEmptyEdges()const;						//returns the amount of empty edges of the board
	int numberOfBoxes(char a)const;						//returns amount of boxes filled with a specific character
	int numberFilledBoxes()const; 						//returns the amount of filled boxes

	bool doMove(int move, bool mc);						//tries to do a move (true if a move is done, false if not)
	bool doCompleteMove(bool hori, int number);
	void doRandomMove(bool mc);
	int randomPlayout(double &ratio);					//will change the gameboard, so only use with copy...
	bool checkIfBoxCompleted(int i, int j);
	int getBoxSide(int i, int j, int side);
	bool doGetFreeBox();											//does move to get free box if possible (returns true if it worked, false if there is no "free box")

	bool horizontal[(maxSize+1) * maxSize];
	bool vertical[(maxSize+1) * maxSize];
	char board[maxSize][maxSize];
	bool playerToMove;									//the player that has to do a turn (false = player 1, true = player2)


private:

	int horizontalEdges;
	int verticalEdges;
	int height;											//the actual height of the board
	int width;											//the actual width of the board
	int numberOfGames;									//the number of games to be played
	// void doActualMove(int i, int j, const int side);	//Actually changes the board




};

class Player {
protected:
    Dotsboxes* game;
public:
    virtual void doMove(){};
		virtual ~Player(){};
};

Dotsboxes::Dotsboxes(){
}

Dotsboxes::Dotsboxes(int w, int h){
	if(w > maxSize){
		width = maxSize;
	}
	else if(w < minSize){
		width = minSize;
	}
	else{
		width = w;
	}

	if(h > maxSize){
		height = maxSize;
	}
	else if(h < minSize){
		height = minSize;
	}
	else{
		height = h;
	}

	verticalEdges = height * (width +1);
	horizontalEdges = (height +1) * width;

	cleanBoard();
}

// Dotsboxes::~Dotsboxes(){
// }

void Dotsboxes::print(){
	char character = 'A';
	char owner;

	for(int i = 0; i < height; ++i){

		for(int j = (i*width); j < ((i+1) * width); ++j){
			character = (horizontal[j]) ? '_' : '`';
			std::cout << " " << character;
		}
		std::cout << std::endl;

		for(int j = (i*( width+1)); j < ((i+1) * (width + 1)); ++j){
			character = (vertical[j]) ? '|' : '`';
			owner = board[i][j % (width+1)];
			std::cout << character << owner ;
		}
		std::cout << std::endl;
	}
	for(int j = (height*width); j < ((height+1) * width); ++j){
			character = (horizontal[j]) ? '_' : '`';
			std::cout << " " << character;
	}
	std::cout << std::endl;
	std::cout << numberOfEmptyEdges() <<std::endl;

	if(whois() == false){
		std::cout << "It is now player1's turn" << std::endl;
	}
	else{
		std::cout << "It is now player2's turn" << std::endl;
	}
	std::cout << std::endl;
}

void Dotsboxes::cleanBoard(){
	for(int i = 0; i < maxSize * (maxSize +1); ++i){
		horizontal[i] = false;
		vertical[i] = false;
	}
	for(int i = 0; i < maxSize; ++i){
		for(int j = 0; j < maxSize; ++j){
			board[i][j] = ' ';
		}
	}

	playerToMove = false; //set playerToMove to player 1 (out of 2)
}

bool Dotsboxes::whois(){
	return playerToMove;
}

void Dotsboxes::changeTurn(){
	playerToMove = !playerToMove;
}

int Dotsboxes::numberOfEmptyEdges()const{
	int emptyEdges = 0;
	//check first row of horizontal lines
	for(int i = 0; i < horizontalEdges; ++i){
		if(horizontal[i] == false){
			emptyEdges++;
		}
	}

	for(int i = 0; i < verticalEdges; ++i){
		if(vertical[i] == false){
			emptyEdges++;
		}
	}

	return emptyEdges;
}


//Function that returns the number of boxes that contain the specific character
int Dotsboxes::numberOfBoxes(char a)const{
	int counter = 0;
	for(int i = 0; i < height; ++i){
		for(int j = 0; j < width; ++j){
			if(board[i][j] == a){
				counter++;
			}
		}
	}
	return counter;
}

//Function that return the number of filled boxes
int Dotsboxes::numberFilledBoxes()const{
	int counter = 0;
	for(int i = 0; i < height; ++i){
		for(int j = 0; j < width; ++j){
			if(board[i][j] != ' '){
				counter++;
			}
		}
	}
	return counter;
}

void Dotsboxes::getWinner(int &result, double &ratio){
	int boxes1 = numberOfBoxes('A');
	int boxes2 = numberOfBoxes('B');


	if(boxes1 == boxes2){
		result = 2;//return tie
	}
	else if(boxes1 > boxes2){
		result = 0;//return win player1
		ratio = (double)boxes1/(double)(boxes1+boxes2);
	}
	else if(boxes2 > boxes1){
		result = 1;//return win player2
		ratio = (double)boxes2/(double)(boxes1+boxes2);
	}
	else{
		std::cout << "something went wronk in Dotsboxes::getwinner!" << std::endl;
	}
}

int Dotsboxes::getBoxSide(int i, int j, int side){
	switch(side){
		case UP: 	return ((i * width) + j);
		case RIGHT: return ((i * (width +1)) + j);
		case DOWN:	return (((i+1) * width) + j);
		case LEFT:	return ((i * (width +1)) + j + 1);
		default: 	std::cout <<"something went wronk in getboxside" << std::endl;
					break;
	}
	return -1;
}

bool Dotsboxes::checkIfBoxCompleted(int i, int j){
	int horizontal1 = (i 		* 	width) 		+ j;
	int horizontal2 = ((i+1) 	* 	width) 		+ j;
	int vertical1	= (i 		* 	(width +1))	+ j;
	int vertical2 	= vertical1 + 1;

	return (horizontal[horizontal1] && vertical[vertical1] &&
					horizontal[horizontal2] && vertical[vertical2]);
}

//Checks if other boxes must also be adjusted
bool Dotsboxes::doCompleteMove(bool hori, int number){
	int prevFilledBoxes, filledBoxes;
	bool newFilled = false;
	int i = -1;
	int j = -1;
	int character = whois() ? 'B' : 'A';
	if (hori){
		horizontal[number] = true;
	}
	else{
		vertical[number] = true;
	}

	if(hori){
		i = number / width;
		j = number % width;
		//check if the box above it was completed
		if((number - width) >= 0){
			if(checkIfBoxCompleted(i-1, j)){
				board[(i-1)][j] = character;
				newFilled = true;
			}
		}
		//check if the box below it was completed
		if((number + width) < horizontalEdges){
			if(checkIfBoxCompleted((i), j)){
				board[i][j] = character;
				newFilled = true;
			}
		}
	}
	else{
		//get the i&j for the box to the right of the vertical line
		i = number / (width+1);
		j = number %(width+1);
		//check if the box to the right was completed
		if((j + 1) < (width +1)){
			if(checkIfBoxCompleted(i, j)){
				board[i][j] = character;
				newFilled = true;
			}
		}
		//check if the box to the left was completed
		if((j - 1) >= 0){
			if(checkIfBoxCompleted(i, j-1)){
				board[i][j-1] = character;
				newFilled = true;
			}
		}
	}



	if(!newFilled){
		changeTurn();
	}

	return true;
}



//Actually do the move given that it is possible (return false if not possible)
//This function works for random players / monte carlo (might be difficult to select a proper move with heuristics)
bool Dotsboxes::doMove(int move, bool mc = false){
	if(!(move < numberOfEmptyEdges() || move >= 0)){
		return false;
	}

	for(int i = 0; i < horizontalEdges; ++i){
		if(horizontal[i] == false){
			move--;
			if(move < 0){
				doCompleteMove(true, i); //1 for horizontal and i for number
				return true;
			}
		}
	}

	for(int i = 0; i < verticalEdges; ++i){
		if(vertical[i] == false){
			move--;
			if(move < 0){
				doCompleteMove(false, i); //0 for vertical and i for number
				return true;
			}
		}
	}
return false;
}



void Dotsboxes::doRandomMove(bool mc = false){
	// if(doGetFreeBox()){
	// 	return;
	// }
	if(!doMove((rand() % numberOfEmptyEdges()), mc)){
		std::cout << "er gaat iets heel erg fout in random move :'D" << std::endl;
	}
}

//will change the game board
int Dotsboxes::randomPlayout(double &ratio){
	int result;
	// std::cout << "dit is een playout" << std::endl;
	while(numberOfEmptyEdges() > 0){
		if(gEnhancement){
			if(!doGetFreeBox())
				doRandomMove(true);
		}
		else
			doRandomMove(true);
	}

	getWinner(result, ratio);
	return result;
}

bool Dotsboxes::doGetFreeBox(){
	int sides = -1;
	int up, right, left, down;
	int checkUp, checkRight, checkLeft, checkDown;
	int toCheckI = -1, toCheckJ= -1;
	int toDoSide = -1; // 0 = up, 1 = right, 2 = down, 3 = left
	int toDoMove = -1;
	//try to finish a box
	for(int i = 0; i < height; ++i){
		for(int j = 0; j < width; ++j){
			sides = 0;
			up = getBoxSide(i, j, UP);
			right = getBoxSide(i, j, RIGHT);
			down = getBoxSide(i, j, DOWN);
			left = getBoxSide(i, j, LEFT);
			sides += ((int)(horizontal[up]) + (int)(horizontal[down])
													+ (int)(vertical[right])
													+ (int)(vertical[left]));

			if(sides == 3){
				if(horizontal[up] == false){
					toCheckI = i - 1;
					toCheckJ = j;
					toDoSide = UP;
				}
				else if(horizontal[down] == false){
					toCheckI = i + 1;
					toCheckJ = j;
					toDoSide = DOWN;
				}
				else if(vertical[right] == false){
					toCheckI = i;
					toCheckJ = j + 1;
					toDoSide = RIGHT;
				}
				else if(vertical[left] == false){
					toCheckI = i;
					toCheckJ = j - 1;
					toDoSide = LEFT;
				}
				else{
					std::cout << "somethink went wronk in greedymove" << std::endl;
					return false;
				}

				sides = 0;
				if(toCheckI >= 0 && toCheckI < width && toCheckJ >= 0 && toCheckJ < height){
					checkUp = getBoxSide(toCheckI, toCheckJ, UP);
					checkRight = getBoxSide(toCheckI, toCheckJ, RIGHT);
					checkDown = getBoxSide(toCheckI, toCheckJ, DOWN);
					checkLeft = getBoxSide(toCheckI, toCheckJ, LEFT);
					sides += ((int)(horizontal[checkUp]) + (int)(horizontal[checkDown])
															+ (int)(vertical[checkRight])
															+ (int)(vertical[checkLeft]));
				}

				if(sides == 2){
					//do not do move, and continue
				}
				else{
					//do move and return true;
					toDoMove = getBoxSide(i, j, toDoSide);
					if(toDoSide == UP || toDoSide == DOWN){
						doCompleteMove(true, toDoMove);
					}
					else{
						doCompleteMove(false, toDoMove);
					}
					return true;
				}
			}
		}
	}
	return false;
}
