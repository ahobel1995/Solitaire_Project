#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include "solFunc.h"
#include "gameLogic.h"

void cardMove(int play[19][7], int hidden[19][7], int cardPos[2], int cardMovePos[2]) {
    int i;
    int temp[13];
    for (i = 0; i < 14; i++) {
        if (play[cardPos[0]+i][cardPos[1]] == 0) {
            break;
        }
        temp[i] = play[cardPos[0]+i][cardPos[1]];
        play[cardPos[0]+i][cardPos[1]] = 0;
    }
    play[cardPos[0]][cardPos[1]] = 0;
    for (i = 0; i < 14; i++) {
        play[cardMovePos[0]+i][cardMovePos[1]] = temp[i];
    }
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
    } else if ((play[cardPos[0]][cardPos[1]] - 1) % 13 == (play[cardMovePos[0] - 1][cardMovePos[1]] - 1) % 13 - 1 &&
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

void playerMoveDecision(int play[19][7], int playerCardChoice[2], int playerMoveChoice[2]){
    int i;
    printf("Please input the column you would like to select for a move: ");
    while (scanf("%d", &playerCardChoice[1]) != 1 || playerCardChoice[1] < 1 || playerCardChoice[1] > 7) {
        while (getchar() != '\n');
        printf("Error. Please input a number between 1 and 7: ");
    }
    printf("Please input the row of the card you would like to move: ");
    while (scanf("%d", &playerCardChoice[0]) != 1 || playerCardChoice[0] < 1 || playerCardChoice[0] > 19) {
        while (getchar() != '\n');
        printf("Error. Please input a number between 1 and 19: ");
    }
    printf("Please input the column you would like to move to: ");
    while (scanf("%d", &playerMoveChoice[1]) != 1 || playerMoveChoice[1] < 1 || playerMoveChoice[1] > 7) {
        while (getchar() != '\n');
        printf("Error. Please input a number between 1 and 7: ");
    }

    playerCardChoice[0] = playerCardChoice[0] - 1;
    playerCardChoice[1] = playerCardChoice[1] - 1;
    playerMoveChoice[1] = playerMoveChoice[1] - 1;

    for (i = 19; i > 0; i--) {
        playerMoveChoice[0] = i - 1;
        if (play[playerMoveChoice[0]][playerMoveChoice[1]] != 0) {
            playerMoveChoice[0] = i;
            break;
        }
    }

    printf("\nPlayer Choice: %d", play[playerCardChoice[0]][playerCardChoice[1]]);
    printf("\nPlayer Move: %d", play[playerMoveChoice[0]][playerMoveChoice[1]]);
    printf("\nPlayer Move Above: %d", play[playerMoveChoice[0]-1][playerMoveChoice[1]]);
    printf("\nPlayer Move Above mod: %d", play[playerMoveChoice[0]-1][playerMoveChoice[1]]%13);
    printf("\nPlayer Move Above mod-1: %d", (play[playerMoveChoice[0]-1][playerMoveChoice[1]]-1)%13-1);
    printf("\nPlayer Choice mod: %d\n", (play[playerCardChoice[0]][playerCardChoice[1]]-1)%13);
    sleep(5);
}