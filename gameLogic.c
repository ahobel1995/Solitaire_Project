#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include "solFunc.h"
#include "gameLogic.h"

void cardMove(int play[19][7], int hidden[19][7], int cardPos[2], int cardMovePos[2]) {
    int temp;
    temp = play[cardPos[0]][cardPos[1]];
    play[cardPos[0]][cardPos[1]] = 0;
    play[cardMovePos[0]][cardMovePos[1]] = temp;
    if (hidden[cardPos[0] - 1][cardPos[1]] == 99) {
        hidden[cardPos[0] - 1][cardPos[1]] = 0;
    }
}

void cardMoveEval(int play[19][7], int hidden[19][7], int cardPos[2], int cardMovePos[2]) {
    if (play[cardPos[0]][cardPos[1]] == 0) {
        printf("Error. Please choose a card.\n");
        sleep(3);
        return;
        // The following check is to ensure the card is one lower, opposite suit, and not a king for a valid move.
    } else if (play[cardPos[0]][cardPos[1]] % 13 == play[cardMovePos[0] - 1][cardMovePos[1]] % 13 - 1 &&
            (((play[cardPos[0]][cardPos[1]] >= 1 && play[cardPos[0]][cardPos[1]] <= 13) ||
              (play[cardPos[0]][cardPos[1]] >= 27 && play[cardPos[0]][cardPos[1]] <= 39)) !=
             ((play[cardMovePos[0] - 1][cardMovePos[1]] >= 1 && play[cardMovePos[0] - 1][cardMovePos[1]] <= 13) ||
              (play[cardMovePos[0] - 1][cardMovePos[1]] >= 27 && play[cardMovePos[0] - 1][cardMovePos[1]] <= 39))) &&
               play[cardPos[0]][cardPos[1]] % 13 != 0) {
        cardMove(play, hidden, cardPos, cardMovePos);
        printf("Valid move.\n");
        // This check is to check for a King and then ensures the move position is the top row.
    } else if (play[cardPos[0]][cardPos[1]] % 13 == 0 && cardMovePos[0] == 0) {
        cardMove(play, hidden, cardPos, cardMovePos);
        printf("Valid move.\n");
    } else {
        printf("Error. Please choose a valid move position.\n");
        sleep(3);
        return;
    }
}