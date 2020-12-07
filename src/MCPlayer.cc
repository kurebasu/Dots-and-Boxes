/*
*File: MCPlayer.cc
*Author: Said Krebbers (s1381164)
*Last edit date: -
*/




class MCPlayer : public Player{
public:
	MCPlayer(Dotsboxes* g);	//constructor;
	void doMove();
};


MCPlayer::MCPlayer(Dotsboxes* g){
	game = g;
}


void MCPlayer::doMove(){

	Dotsboxes gameCopy;
	int numberOfMoves = game->numberOfEmptyEdges();
	int result = -9999999;
	double ratio = 0;
	int bestMove = -9999999;
	double currentScore, lossScore, ties, bestMoveScore = -9999999;
	bool done;



	int player = 0;
	if(game->whois() == true){
		player = 1;
	}

	// std::cout << "START VAN MC OUTPUT" << std::endl;
	for(int i = 0; i < numberOfMoves; ++i){
		currentScore = 0;
		lossScore = 0;
		ties = 0;
		done = false;

		for(int j = 0; j < (gIterations/numberOfMoves); ++j){
			gameCopy = *game;
			gameCopy.doMove(i, true);
			// if(!done){
			// 	done = !done;
			// 	std::cout << "move: " << i << std::endl;
			// 	gameCopy.print();
			// }

			result = gameCopy.randomPlayout(ratio);
			//if this player won
			if(result == player){
				// std::cout << "ratio = " << ratio << std::endl;
				// currentScore+= ratio;
				currentScore++;
			}
			//it is no tie, so a loss
			else if (result != 2){
				// currentScore-= ratio;
				lossScore++;
			}
			else{
				ties++;
			}
			// std::cout << "end of one game for move check" << std::endl;
		}
		if(currentScore > bestMoveScore){
			bestMoveScore = currentScore;
			bestMove = i;
		}
		// std::cout << "end of one move check " << i << " currentscore: " << currentScore << "/" << lossScore <<"/" << ties << std::endl << std::endl;


	}
	// std::cout << "EINDE VAN MC OUTPUT" << std::endl;
	// std::cout << "bestMoveScore = " << bestMoveScore << "/" << (gIterations/numberOfMoves) << "   out of: " << numberOfMoves << std::endl;
	game->doMove(bestMove);

}
