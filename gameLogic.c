#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "solFunc.h"

void cardMove(int play[19][7], int hidden[19][7], int cardPos[2], int cardMove[2]){
    int temp;
    temp = play[cardPos[0]][cardPos[1]];
    play[cardPos[0]][cardPos[1]] = 0;
    play[cardMove[0]][cardMove[1]] = temp;
    if (hidden[cardPos[0]-1][cardPos[1]] == 99){
        hidden[cardPos[0]][cardPos[1]] = 0;
    }
}