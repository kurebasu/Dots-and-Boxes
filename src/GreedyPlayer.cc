/*
*File: GreedyPlayer.cc
*Author: Said Krebbers (s1381164)
*Last edit date: -
*/


class GreedyPlayer : public Player{
public:
	GreedyPlayer(Dotsboxes* g);	//constructor;
	void doMove();
private:
	bool doGreedyMove();
	bool doSafeMove();
};


GreedyPlayer::GreedyPlayer(Dotsboxes* g){
	game = g;
}

bool GreedyPlayer::doGreedyMove(){
	int sides = -1;
	int height = game->getHeight();
	int width = game->getWidth();
	int up, right, left, down;
	//try to finish a box
	for(int i = 0; i < height; ++i){
		for(int j = 0; j < width; ++j){
			sides = 0;
			up = game->getBoxSide(i, j, UP);
			right = game->getBoxSide(i, j, RIGHT);
			down = game->getBoxSide(i, j, DOWN);
			left = game->getBoxSide(i, j, LEFT);
			sides += ((int)(game->horizontal[up]) + (int)(game->horizontal[down])
					 							  + (int)(game->vertical[right])
												  + (int)(game->vertical[left]));

			if(sides == 3){
				if(game->horizontal[up] == false){
					game->doCompleteMove(true, up);
				}
				else if(game->horizontal[down] == false){
					game->doCompleteMove(true, down);
				}
				else if(game->vertical[right] == false){
					game->doCompleteMove(false, right);
				}
				else if(game->vertical[left] == false){
					game->doCompleteMove(false, left);
				}
				else{
					std::cout << "somethink went wronk in greedymove" << std::endl;
					return false;
				}
				return true;
			}
		}
	}
	return false;
}

//returns true if it found a move
bool GreedyPlayer::doSafeMove(){
	//not implemented yet as it is unclear if i will need this
	return false;
}

void GreedyPlayer::doMove(){
	if(doGreedyMove()){
		return;
	}
	// else if(doSafeMove()){
	// 	return;
	// }
	// else
		game->doRandomMove();
}
