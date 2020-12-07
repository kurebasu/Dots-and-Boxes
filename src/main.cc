/*
*File: main.cc
*Author: Said Krebbers (s1381164)
*Last edit date: -
*/

 int gIterations = 1000;
 bool gMCTSprint      = true;
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <bits/stdc++.h>
#include "dotsboxes.cc"
#include "randomPlayer.cc"
#include "GreedyPlayer.cc"
#include "MCPlayer.cc"
#include "MCTSPlayer.cc"

void bruteForce(int &wins, int &losses, int &ties, int depth, Dotsboxes *a,  bool whois){
	int result = 0;
	double ratio = 0;
	int numberOfMoves = a->numberOfEmptyEdges();
	if(depth > 0){
		if(numberOfMoves == 0){
			a->getWinner(result, ratio);
			if(result == (int)whois){
				wins++;
			}
			else if(result == 2){
				ties++;
			}
			else{
				losses++;
			}
			return;
		}
	}
	Dotsboxes gameCopy;
	depth+=1;
	for(int i = 0; i < numberOfMoves; ++i){
		if(depth == 1){
			wins = losses = ties = 0;
		}
		gameCopy = *a;
		gameCopy.doMove(i, true);

		bruteForce(wins, losses, ties, depth, &gameCopy, whois);

		if(depth == 1){
			std::cout << "for move: " << i << "    the bruteforce results are wins/losses/ties: " << wins << " / " << losses << " / " << ties << std::endl;
		}
	}
}

void printRules(){
	std::cout << "Welkom bij mijn kamertje verhuren programma." << std::endl;
}

void printError(){
	std::cout << "hipity hoopid, are you stoopid? too little arguments" << std::endl;
	std::cout << "expected: " << "./programma" << " [height] [width] [numberOfGames] [MC interations] [player1] [player2] [print] [printMCTStree0/1]" <<std::endl;
  std::cout << "players are 0-4: Random(0), Greedy(1), MC(2), MCTS(3)" <<std::endl;
}

void processResult(int result, int &player1Wins, int &player2Wins, int &ties){
  if(result == 0){
    player1Wins++;
  }
  else if(result == 1){
    player2Wins++;
  }
  else if(result == 2){
    ties++;
  }
}

int main(int argc, char* argv[]){
	printRules();
	if(argc != 9){
		printError();
		return 1;
	}
	srand(time(NULL));
	int result = -1;

	int rows = atoi (argv[1]);
	int columns = atoi (argv[2]);
	int numberOfGames = atoi (argv[3]);
	gIterations = atoi (argv[4]);
  int whichPlayer1 = atoi (argv[5]);
  int whichPlayer2 = atoi (argv[6]);
  bool print = atoi (argv[7]);
  gMCTSprint = atoi (argv[8]);


  Player* player1;
  Player* player2;

  Dotsboxes* game = new Dotsboxes(columns, rows);
  switch(whichPlayer1){
    case 0: player1 = new RandomPlayer(game);
            std::cout << "player1 = randomPlayer" << std::endl;
            break;
    case 1: player1 = new GreedyPlayer(game);
            std::cout << "player1 = greedyPlayer" << std::endl;
            break;
    case 2: player1 = new MCPlayer(game);
            std::cout << "player1 = MCPlayer" << std::endl;
            break;
    case 3: player1 = new MCTSPlayer(game);
            std::cout << "player1 = MCTSPlayer" << std::endl;
            break;
    default:std::cout << "speler " << whichPlayer1 << " bestaat niet, we kiezen de random speler voor 1" << std::endl;
            player1 = new RandomPlayer(game);
  }

  switch(whichPlayer2){
    case 0: player2 = new RandomPlayer(game);
            std::cout << "player2 = randomPlayer" << std::endl;
            break;
    case 1: player2 = new GreedyPlayer(game);
            std::cout << "player2 = greedyPlayer" << std::endl;
            break;
    case 2: player2 = new MCPlayer(game);
            std::cout << "player2 = MCPlayer" << std::endl;
            break;
    case 3: player2 = new MCTSPlayer(game);
            std::cout << "player2 = MCTSPlayer" << std::endl;
            break;
    default:std::cout << "speler " << whichPlayer2 << " bestaat niet, we kiezen de random speler voor 2" << std::endl;
            player2 = new RandomPlayer(game);
  }

	int player1Wins = 0;
	int player2Wins = 0;
	int ties = 0;
	double unused;

  // bruteForce(player1Wins, player2Wins, ties, 0, game, 0);

  int gepakt = 0;
	int turn = 0;
	for(int i = 0; i < numberOfGames; ++i){
		turn = 0;
		game->cleanBoard();

		do{
			if(game->whois() == false){
				player1->doMove();
			}
			else{
				player2->doMove();
			}

      if(print){
			  game->print(); //prints every turn
      }
      if(turn == 0 && game->numberFilledBoxes() > 0){
        gepakt++;
      }

      turn++;
		}while(game->numberOfEmptyEdges() > 0);

    game->getWinner(result, unused);
    processResult(result, player1Wins, player2Wins, ties);

    if(print){
  		std::cout << "score = " << game->numberOfBoxes('A') << " - " << game->numberOfBoxes('B') << std::endl;
  		std::cout << "-----------------------end of game---------------------------" << std::endl;
    }
		if(i % 10 == 0){
			std::cout << "done: " << i+1 << " games." << std::endl;
		}
	}
  std::cout << "gepakt in eerste beurt: " << gepakt << "/" << numberOfGames  << std::endl;
  	std::cout << "player1: " << player1Wins << "  player2: " << player2Wins << "  ties: " << ties << std::endl;
	delete game;
    return 0;
}


// game->playerToMove = true;
// game->doCompleteMove(true, 0);
// game->playerToMove = true;
// game->doCompleteMove(true, 1);
// game->playerToMove = true;
// game->doCompleteMove(true, 3);
// game->playerToMove = true;
// game->doCompleteMove(true, 6);
// game->playerToMove = true;
// game->doCompleteMove(true, 7);
// game->playerToMove = true;
// game->doCompleteMove(false, 2);
// game->playerToMove = false;
// game->print();



// game->playerToMove = true;
// game->doCompleteMove(true, 0);
// game->playerToMove = true;
// game->doCompleteMove(false, 0);
// game->playerToMove = true;
// game->doCompleteMove(true, 1);
// game->playerToMove = false;
// game->print();

//
// game->cleanBoard();
// game->doCompleteMove(true, 0);
// game->doCompleteMove(false, 0);
// game->doCompleteMove(false, 1);
// game->playerToMove = false;
