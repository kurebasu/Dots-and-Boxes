#!/bin/bash
#Shell script die alle tests in een keer uitvoert, programma moet al gebuild zijn.
# ./programma [height] [width] [numberOfGames] [MC interations] [player1] [player2] [print] [printMCTStree0/1]
# players are 0-4: Random(0), Greedy(1), MC(2), MCTS(3)


./programma 3 3 1000 1000 0 0 0 0 > tests/test0-0.txt;
echo "1 out of 16";
./programma 3 3 1000 1000 0 1 0 0 > tests/test0-1.txt;
echo "2 out of 16";
./programma 3 3 1000 1000 0 2 0 0 > tests/test0-2.txt;
echo "3 out of 16";
./programma 3 3 1000 1000 0 3 0 0 > tests/test0-3.txt;
echo "4 out of 16";
./programma 3 3 1000 1000 1 0 0 0 > tests/test1-0.txt;
echo "5 out of 16";
./programma 3 3 1000 1000 1 1 0 0 > tests/test1-1.txt;
echo "6 out of 16";
./programma 3 3 1000 1000 1 2 0 0 > tests/test1-2.txt;
echo "7 out of 16";
./programma 3 3 1000 1000 1 3 0 0 > tests/test1-3.txt;
echo "8 out of 16";
./programma 3 3 1000 1000 2 0 0 0 > tests/test2-0.txt;
echo "9 out of 16";
./programma 3 3 1000 1000 2 1 0 0 > tests/test2-1.txt;
echo "10 out of 16";
./programma 3 3 1000 1000 2 2 0 0 > tests/test2-2.txt;
echo "11 out of 16";
./programma 3 3 1000 1000 2 3 0 0 > tests/test2-3.txt;
echo "12 out of 16";
./programma 3 3 1000 1000 3 0 0 0 > tests/test3-0.txt;
echo "13 out of 16";
./programma 3 3 1000 1000 3 1 0 0 > tests/test3-1.txt;
echo "14 out of 16";
./programma 3 3 1000 1000 3 2 0 0 > tests/test3-2.txt;
echo "15 out of 16";
./programma 3 3 1000 1000 3 3 0 0 > tests/test3-3.txt;
echo "16 out of 16";
