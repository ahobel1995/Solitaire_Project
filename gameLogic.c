#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include "solFunc.h"
#include "gameLogic.h"

void cardMove(int play[19][7], int hidden[19][7], int cardPos[2], int cardMovePos[2]) {
    int i, j;
    int temp[13];
    for (i = 0; i < 13; i++) {
        if (play[cardPos[0] + i][cardPos[1]] == 0) {
            temp[i] = 0;
            break;
        }
        temp[i] = play[cardPos[0] + i][cardPos[1]];
        play[cardPos[0] + i][cardPos[1]] = 0;
    }
    play[cardPos[0]][cardPos[1]] = 0;
    for (i = 0; i < 13; i++) {
        if (temp[i] == 0) {
            break;
        }
        play[cardMovePos[0] + i][cardMovePos[1]] = temp[i];
    }
    if (hidden[cardPos[0] - 1][cardPos[1]] == 99) {
        hidden[cardPos[0] - 1][cardPos[1]] = 0;
    }
}

void cardMoveDrop(int play[19][7], int cardPos[2], int dropDeck[4]) {
    switch (play[cardPos[0]][cardPos[1]]) {
        case 1 ... 13 :
            dropDeck[0] = play[cardPos[0]][cardPos[1]];
            break;
        case 14 ... 26 :
            dropDeck[1] = play[cardPos[0]][cardPos[1]];
            break;
        case 27 ... 39 :
            dropDeck[2] = play[cardPos[0]][cardPos[1]];
            break;
        case 40 ... 52 :
            dropDeck[3] = play[cardPos[0]][cardPos[1]];
            break;
    }
}

void cardMoveEval(int play[19][7], int hidden[19][7], int cardPos[2], int cardMovePos[2], int dropDeck[4]) {
    if (play[cardPos[0]][cardPos[1]] == 0) {
        printf("Error. Please choose a card.\n");
        sleep(3);

        // The following check is to ensure the card is one value lower, opposite suit for a valid move.
    } else if ((play[cardPos[0]][cardPos[1]] - 1) % 13 == ((play[cardMovePos[0] - 1][cardMovePos[1]] - 1) % 13 - 1) &&
               (((play[cardPos[0]][cardPos[1]] >= 1 && play[cardPos[0]][cardPos[1]] <= 13) ||
                 (play[cardPos[0]][cardPos[1]] >= 27 && play[cardPos[0]][cardPos[1]] <= 39)) !=
                ((play[cardMovePos[0] - 1][cardMovePos[1]] >= 1 && play[cardMovePos[0] - 1][cardMovePos[1]] <= 13) ||
                 (play[cardMovePos[0] - 1][cardMovePos[1]] >= 27 && play[cardMovePos[0] - 1][cardMovePos[1]] <= 39)))) {
        cardMove(play, hidden, cardPos, cardMovePos);
        printf("Valid move.\n");

        // If the move position is the top row, this ensures it is empty.
    } else if (cardMovePos[0] == 0 && play[cardMovePos[0]][cardMovePos[1]] == 0) {
        cardMove(play, hidden, cardPos, cardMovePos);
        printf("Valid move.\n");

        // Drop Deck evaluation
    } else if (cardMovePos[1] == 8) {
        if (play[cardPos[0]][cardPos[1] + 1] != 0) {
            printf("Invalid Selection. Your card must be singular and not in a stack for the drop deck.\n");
            sleep(3);
        } else {
            switch (play[cardPos[0]][cardPos[1]]) {
                case 1 ... 13 :
                    if (play[cardMovePos[0]][cardMovePos[1]]%13 == (dropDeck[0] + 1)%13) {
                        cardMoveDrop(play, cardPos, dropDeck);
                        printf("Valid move.\n");
                    } else {
                        printf("Invalid move. Please Select Valid Card for Hearts Drop Deck.\n");
                        sleep(3);
                    }
                    break;
                case 14 ... 26 :
                    if (play[cardMovePos[0]][cardMovePos[1]]%13 == (dropDeck[1] + 1)%13) {
                        cardMoveDrop(play, cardPos, dropDeck);
                        printf("Valid move.\n");
                    } else {
                        printf("Invalid move. Please Select Valid Card for Clubs Drop Deck.\n");
                        sleep(3);
                    }
                    break;
                case 27 ... 39 :
                    if (play[cardMovePos[0]][cardMovePos[1]]%13 == (dropDeck[2] + 1)%13) {
                        cardMoveDrop(play, cardPos, dropDeck);
                        printf("Valid move.\n");
                    } else {
                        printf("Invalid move. Please Select Valid Card for Diamonds Drop Deck.\n");
                        sleep(3);
                    }
                    break;
                case 40 ... 52 :
                    if (play[cardMovePos[0]][cardMovePos[1]]%13 == (dropDeck[3] + 1)%13) {
                        cardMoveDrop(play, cardPos, dropDeck);
                        printf("Valid move.\n");
                    } else {
                        printf("Invalid move. Please Select Valid Card for Hearts Drop Deck.\n");
                        sleep(3);
                    }
                    break;
            }
        }
    } else {
        printf("Error. Please choose a valid move position.\n");
        sleep(3);
    }
}

int playerMoveDecision(int play[19][7], int playerCardChoice[2], int playerMoveChoice[2]) {
    int i;
    printf("Please input the column you would like to select for a move: ");
    while (scanf("%d", &playerCardChoice[1]) != 1 || playerCardChoice[1] < 1 || playerCardChoice[1] > 11) {
        while (getchar() != '\n');
        printf("Error. Please input a number between 1 and 11: ");
    }
    printf("Please input the row of the card you would like to move: ");
    while (scanf("%d", &playerCardChoice[0]) != 1 || playerCardChoice[0] < 1 || playerCardChoice[0] > 19) {
        while (getchar() != '\n');
        printf("Error. Please input a number between 1 and 19: ");
    }
    printf("Please input the column you would like to move to: ");
    while (scanf("%d", &playerMoveChoice[1]) != 1 || playerMoveChoice[1] < 1 || playerMoveChoice[1] > 11) {
        while (getchar() != '\n');
        printf("Error. Please input a number between 1 and 8 (8 for the drop decks): ");
    }

    playerCardChoice[0]--;
    playerCardChoice[1]--;
    playerMoveChoice[1]--;

    for (i = 19; i > 0; i--) {
        playerMoveChoice[0] = i - 1;
        if (play[playerMoveChoice[0]][playerMoveChoice[1]] != 0) {
            playerMoveChoice[0] = i;
            break;
        }
    }
    /*
    //DEBUG
    printf("\nPlayer Choice: %d", play[playerCardChoice[0]][playerCardChoice[1]]);
    printf("\nPlayer Move: %d", play[playerMoveChoice[0]][playerMoveChoice[1]]);
    printf("\nPlayer Move Above: %d", play[playerMoveChoice[0]-1][playerMoveChoice[1]]);
    printf("\nPlayer Move Above mod: %d", (play[playerMoveChoice[0]-1][playerMoveChoice[1]]-1)%13);
    printf("\nPlayer Move Above mod - 1: %d", ((play[playerMoveChoice[0]-1][playerMoveChoice[1]]-1)%13)-1);
    printf("\nPlayer Choice mod: %d\n", (play[playerCardChoice[0]][playerCardChoice[1]]-1)%13);
    //DEBUG
    */
    return 0;
}