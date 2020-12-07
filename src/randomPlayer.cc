/*
*File: randomPlayer.cc
*Author: Said Krebbers (s1381164)
*Last edit date: -
*/

class RandomPlayer : public Player{
public:
	RandomPlayer(Dotsboxes* g);	//constructor;
	void doMove();
};


RandomPlayer::RandomPlayer(Dotsboxes* g){
	game = g;
}

//returns random number between (0, numberOfEmptyEdges)
void RandomPlayer::doMove(){
	game->doRandomMove();
}
