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

void cardMoveDrop(int play[19][7], int hidden[19][7], int cardPos[2], int dropDeck[4]) {
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
    play[cardPos[0]][cardPos[1]] = 0;
    if (hidden[cardPos[0] - 1][cardPos[1]] == 99) {
        hidden[cardPos[0] - 1][cardPos[1]] = 0;
    }
    printf("Drop Deck Updated.\n");
    sleep(3);
}

void cardMoveEval(int play[19][7], int hidden[19][7], int cardPos[2], int cardMovePos[2], int dropDeck[4]) {
    // This checks if the card is hidden.
    if (hidden[cardPos[0]][cardPos[1]] == 99) {
        printf("Error. You cannot choose a hidden card.\n");
        sleep(3);
        return;
    }

        // This checks if the card selected is not empty.
    else if (play[cardPos[0]][cardPos[1]] == 0) {
        printf("Error. Please choose a card.\n");
        sleep(3);
        return;

        // Drop Deck evaluation
    } else if (cardMovePos[1] == 7) {
        if (play[cardPos[0]][cardPos[1] + 1] == 0) {
            printf("Invalid Selection. Your card must be singular and not in a stack for the drop deck.\n");
            sleep(3);
        } else {
            switch (play[cardPos[0]][cardPos[1]]) {
                case 1 ... 13 :
                    if (play[cardPos[0]][cardPos[1]] % 13 == dropDeck[0] % 13 + 1) {
                        cardMoveDrop(play, hidden, cardPos, dropDeck);
                        printf("Valid move.\n");
                    } else {
                        printf("Invalid move. Please Select Valid Card for Hearts Drop Deck.\n");
                        sleep(3);
                    }
                    break;
                case 14 ... 26 :
                    if (play[cardPos[0]][cardPos[1]] % 13 == dropDeck[1] % 13 + 1) {
                        cardMoveDrop(play, hidden, cardPos, dropDeck);
                        printf("Valid move.\n");
                    } else {
                        printf("Invalid move. Please Select Valid Card for Clubs Drop Deck.\n");
                        sleep(3);
                    }
                    break;
                case 27 ... 39 :
                    if (play[cardPos[0]][cardPos[1]] % 13 == dropDeck[2] % 13 + 1) {
                        cardMoveDrop(play, hidden, cardPos, dropDeck);
                        printf("Valid move.\n");
                    } else {
                        printf("Invalid move. Please Select Valid Card for Diamonds Drop Deck.\n");
                        sleep(3);
                    }
                    break;
                case 40 ... 52 :
                    if (play[cardPos[0]][cardPos[1]] % 13 == dropDeck[3] % 13 + 1) {
                        cardMoveDrop(play, hidden, cardPos, dropDeck);
                        printf("Valid move.\n");
                    } else {
                        printf("Invalid move. Please Select Valid Card for Hearts Drop Deck.\n");
                        sleep(3);
                    }
                    break;
            }
        }
        return;

        // The following check is to ensure the card is one value lower, opposite suit for a valid move.
    } else if ((play[cardPos[0]][cardPos[1]] - 1) % 13 == ((play[cardMovePos[0] - 1][cardMovePos[1]] - 1) % 13 - 1) &&
               (((play[cardPos[0]][cardPos[1]] >= 1 && play[cardPos[0]][cardPos[1]] <= 13) ||
                 (play[cardPos[0]][cardPos[1]] >= 27 && play[cardPos[0]][cardPos[1]] <= 39)) !=
                ((play[cardMovePos[0] - 1][cardMovePos[1]] >= 1 && play[cardMovePos[0] - 1][cardMovePos[1]] <= 13) ||
                 (play[cardMovePos[0] - 1][cardMovePos[1]] >= 27 && play[cardMovePos[0] - 1][cardMovePos[1]] <= 39)))) {
        cardMove(play, hidden, cardPos, cardMovePos);
        printf("Valid move (Normal Move).\n");
        sleep(3);
        return;

        // If the move position is the top row, this ensures it is empty.
    } else if (cardMovePos[0] == 0 && play[cardMovePos[0]][cardMovePos[1]] == 0) {
        cardMove(play, hidden, cardPos, cardMovePos);
        printf("Valid move (0 move).\n");
        sleep(3);
        return;

        // Catch all error if nothing else is working.
    } else {
        printf("Error. Please choose a valid move position.\n");
        sleep(3);
        return;
    }
}

void playerMoveDecision(int play[19][7], int hidden[19][7], int dropDeck[4], int deck[53],
                        int playerCardChoice[2], int playerMoveChoice[2], int draw) {
    int i, drawDeckChoice, deckPullChoice = 0;
    do {
        deckPullChoice = 0;
        printf("Would you like to enter draw deck menu? (y=1, n=0) ");
        while (scanf("%d", &drawDeckChoice) != 1 || (drawDeckChoice != 1 && drawDeckChoice != 0)) {
            while (getchar() != '\n');
            printf("Error. Please input a 1 or 0: ");
        }
        if (drawDeckChoice == 1) {
            deckPull(play, deck, playerCardChoice, &draw, hidden, dropDeck, deckPullChoice);
            printf("%d", draw);
            break;
        } else {
            printf("Please input the column you would like to select for a move (1-7): ");
            while (scanf("%d", &playerCardChoice[1]) != 1 || playerCardChoice[1] < 1 || playerCardChoice[1] > 7) {
                while (getchar() != '\n');
                printf("Error. Please input a number between 1 and 7: ");
            }
            printf("Please input the row of the card you would like to move (1-19): ");
            while (scanf("%d", &playerCardChoice[0]) != 1 || playerCardChoice[0] < 1 || playerCardChoice[0] > 19) {
                while (getchar() != '\n');
                printf("Error. Please input a number between 1 and 19: ");
            }
            printf("Please input the column you would like to move to (1-8), 8 is for drop deck: ");
            while (scanf("%d", &playerMoveChoice[1]) != 1 || playerMoveChoice[1] < 1 || playerMoveChoice[1] > 9) {
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
            return;
        }
    } while (deckPullChoice == 3);

    printf("Please input the column you would like to move to (1-8), 8 is for drop deck: ");
    while (scanf("%d", &playerMoveChoice[1]) != 1 || playerMoveChoice[1] < 1 || playerMoveChoice[1] > 9) {
        while (getchar() != '\n');
        printf("Error. Please input a number between 1 and 8 (8 for the drop decks): ");
    }

    playerMoveChoice[1]--;

    for (i = 19; i > 0; i--) {
        playerMoveChoice[0] = i - 1;
        if (play[playerMoveChoice[0]][playerMoveChoice[1]] != 0) {
            playerMoveChoice[0] = i;
            break;
        }
    }

    //DEBUG
    printf("\nPlayer Card Position: [%d, %d]", playerCardChoice[0], playerCardChoice[1]);
    printf("\nPlayer Move Position: [%d, %d]", playerMoveChoice[0], playerMoveChoice[1]);
    printf("\nPlayer Choice: %d", play[playerCardChoice[0]][playerCardChoice[1]]);
    printf("\nPlayer Move: %d", play[playerMoveChoice[0]][playerMoveChoice[1]]);
    printf("\nPlayer Move Above: %d", play[playerMoveChoice[0] - 1][playerMoveChoice[1]]);
    printf("\nPlayer Move Above mod: %d", (play[playerMoveChoice[0] - 1][playerMoveChoice[1]] - 1) % 13);
    printf("\nPlayer Move Above mod - 1: %d", ((play[playerMoveChoice[0] - 1][playerMoveChoice[1]] - 1) % 13) - 1);
    printf("\nPlayer Choice mod: %d\n", (play[playerCardChoice[0]][playerCardChoice[1]] - 1) % 13);
    //DEBUG
}

void deckPull(int play[21][7], int deck[53], int cardPos[2], int *draw, int hidden[21][7], int dropDeck[4],
              int deckPullChoice) {
    int i;
    do {
        printf("Deck Pull choices: (1: select the card, 2: cycle deck, 3: reset to start menu)\n");
        while (scanf("%d", &deckPullChoice) != 1 || deckPullChoice < 1 || deckPullChoice > 3) {
            while (getchar() != '\n');
            printf("Error. Please input a number between 1 and 3: ");
        }
        switch (deckPullChoice) {
            case 1:
                printf("You have selected the card.\n");
                cardPos[0] = 20;
                cardPos[1] = 6;
                play[cardPos[0]][cardPos[1]] = deck[*draw];
                deck[*draw] = 0;
                *draw++;
                printf("%d", *draw);
                for (i = 0; i <= 1; i++) {
                    while (deck[*draw] == 0) {
                        *draw += 1;
                        if (*draw == 53) {
                            *draw = 30;
                            break;
                        }
                    }
                }
                break;
                /*
            case 2:
                printf("You have cycled the deck.\n");
                draw++;
                if (draw < 53) {
                    for (i = 0; i <= 1; i++) {
                        while (deck[draw] == 0) {
                            draw += 1;
                            if (draw == 53) {
                                draw = 30;
                                break;
                            }
                        }
                    }
                } else {
                    draw = 30;
                }
                frameGen(play, hidden, deck, dropDeck, draw);
                break;
            case 3:
                printf("You have reset to the start menu.\n");
                break;
        }
                 */
    } while (deckPullChoice == 2);
    sleep(3);
}