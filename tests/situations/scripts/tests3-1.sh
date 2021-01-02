#!/bin/bash

# ./programma [height] [width] [numberOfGames] [MC interations] [player1] [player2] [print] [printMCTStree0/1]
# players are 0-4: Random(0), Greedy(1), MC(2), MCTS(3)

./programma 3 3 1 1000 3 0 0 1 0 1 > tests/situations/test3.1.0.1;
./programma 3 3 1 1000 3 0 0 1 0 2 > tests/situations/test3.1.0.2;
./programma 3 3 1 1000 3 0 0 1 1 1 > tests/situations/test3.1.1.1;
./programma 3 3 1 1000 3 0 0 1 1 2 > tests/situations/test3.1.1.2;

