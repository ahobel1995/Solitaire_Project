#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include "solFunc.h"
#include "gameLogic.h"

int cardMove(int play[19][7], int hidden[19][7], int cardPos[2], int cardMovePos[2], int* moveCount) {
    int i, j;
    int temp[13];
    (*moveCount)++;
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
    return *moveCount;
}

int cardMoveDrop(int play[19][7], int hidden[19][7], int cardPos[2], int dropDeck[4], int* moveCount) {
    switch (play[cardPos[0]][cardPos[1]]) {
        case 1 ... 13 :
            dropDeck[0] = play[cardPos[0]][cardPos[1]];
            (*moveCount)++;
            break;
        case 14 ... 26 :
            dropDeck[1] = play[cardPos[0]][cardPos[1]];
            (*moveCount)++;
            break;
        case 27 ... 39 :
            dropDeck[2] = play[cardPos[0]][cardPos[1]];
            (*moveCount)++;
            break;
        case 40 ... 52 :
            dropDeck[3] = play[cardPos[0]][cardPos[1]];
            (*moveCount)++;
            break;
    }
    play[cardPos[0]][cardPos[1]] = 0;
    if (hidden[cardPos[0] - 1][cardPos[1]] == 99) {
        hidden[cardPos[0] - 1][cardPos[1]] = 0;
    }
    return *moveCount;
}

int cardMoveEval(int play[19][7], int hidden[19][7], int cardPos[2], int cardMovePos[2], int dropDeck[4], int deck[53],
                 int draw, int* moveptr) {
    int i;
    // This checks if the card is hidden.
    if (hidden[cardPos[0]][cardPos[1]] == 99) {
        printf("Error. You cannot choose a hidden card.\n");
        sleep(3);
        return draw;
    }

        // This checks if the card selected is not empty.
    else if (play[cardPos[0]][cardPos[1]] == 0) {
        printf("Error. Please choose a card.\n");
        sleep(3);
        return draw;

        // Drop Deck evaluation
    } else if (cardMovePos[1] == 7) {
        if (play[cardPos[0] + 1][cardPos[1]] != 0) {
            printf("Invalid Selection. Your card must be singular and not in a stack for the drop deck.\n");
            sleep(3);
        } else {
            switch (play[cardPos[0]][cardPos[1]]) {
                case 1 ... 13 :
                    if (play[cardPos[0]][cardPos[1]] % 13 == dropDeck[0] % 13 + 1 ||
                        play[cardPos[0]][cardPos[1]] == 13) {
                        cardMoveDrop(play, hidden, cardPos, dropDeck, *moveptr);
                        printf("Valid move.\n");
                    } else {
                        printf("Invalid move. Please Select Valid Card for Hearts Drop Deck.\n");
                        sleep(3);
                    }
                    break;
                case 14 ... 26 :
                    if (play[cardPos[0]][cardPos[1]] % 13 == dropDeck[1] % 13 + 1 ||
                        play[cardPos[0]][cardPos[1]] == 26) {
                        cardMoveDrop(play, hidden, cardPos, dropDeck, *moveptr);
                        printf("Valid move.\n");
                    } else {
                        printf("Invalid move. Please Select Valid Card for Clubs Drop Deck.\n");
                        sleep(3);
                    }
                    break;
                case 27 ... 39 :
                    if (play[cardPos[0]][cardPos[1]] % 13 == dropDeck[2] % 13 + 1 ||
                        play[cardPos[0]][cardPos[1]] == 39) {
                        cardMoveDrop(play, hidden, cardPos, dropDeck, *moveptr);
                        printf("Valid move.\n");
                    } else {
                        printf("Invalid move. Please Select Valid Card for Diamonds Drop Deck.\n");
                        sleep(3);
                    }
                    break;
                case 40 ... 52 :
                    if (play[cardPos[0]][cardPos[1]] % 13 == dropDeck[3] % 13 + 1 ||
                        play[cardPos[0]][cardPos[1]] == 52) {
                        cardMoveDrop(play, hidden, cardPos, dropDeck, *moveptr);
                        printf("Valid move.\n");
                    } else {
                        printf("Invalid move. Please Select Valid Card for Hearts Drop Deck.\n");
                        sleep(3);
                    }
                    break;
            }
        }
        if (dropDeck[0] == deck[draw]) {
            deck[draw] = 0;
            for (i = 0; i <= 1; i++) {
                while (deck[draw] == 0) {
                    draw++;
                    if (draw == 53) {
                        draw = 29;
                        break;
                    }
                }
            }
        } else if (dropDeck[1] == deck[draw]) {
            deck[draw] = 0;
            for (i = 0; i <= 1; i++) {
                while (deck[draw] == 0) {
                    draw++;
                    if (draw == 53) {
                        draw = 29;
                        break;
                    }
                }
            }
        } else if (dropDeck[2] == deck[draw]) {
            deck[draw] = 0;
            for (i = 0; i <= 1; i++) {
                while (deck[draw] == 0) {
                    draw++;
                    if (draw == 53) {
                        draw = 29;
                        break;
                    }
                }
            }
        } else if (dropDeck[3] == deck[draw]) {
            deck[draw] = 0;
            for (i = 0; i <= 1; i++) {
                while (deck[draw] == 0) {
                    draw++;
                    if (draw == 53) {
                        draw = 29;
                        break;
                    }
                }
            }
        }
        return draw;

        // The following check is to ensure the card is one value lower, opposite suit for a valid move.
    } else if ((play[cardPos[0]][cardPos[1]] - 1) % 13 == ((play[cardMovePos[0] - 1][cardMovePos[1]] - 1) % 13 - 1) &&
               (((play[cardPos[0]][cardPos[1]] >= 1 && play[cardPos[0]][cardPos[1]] <= 13) ||
                 (play[cardPos[0]][cardPos[1]] >= 27 && play[cardPos[0]][cardPos[1]] <= 39)) !=
                ((play[cardMovePos[0] - 1][cardMovePos[1]] >= 1 && play[cardMovePos[0] - 1][cardMovePos[1]] <= 13) ||
                 (play[cardMovePos[0] - 1][cardMovePos[1]] >= 27 && play[cardMovePos[0] - 1][cardMovePos[1]] <= 39)))) {
        cardMove(play, hidden, cardPos, cardMovePos, *moveptr);
        printf("Valid move (Normal Move).\n");
        if (play[cardMovePos[0]][cardMovePos[1]] == deck[draw]) {
            deck[draw] = 0;
            for (i = 0; i <= 1; i++) {
                while (deck[draw] == 0) {
                    draw++;
                    if (draw == 53) {
                        draw = 29;
                        break;
                    }
                }
            }
        }
        return draw;

        // If the move position is the top row, this ensures it is empty.
    } else if (cardMovePos[0] == 0 && play[cardMovePos[0]][cardMovePos[1]] == 0) {
        cardMove(play, hidden, cardPos, cardMovePos, *moveptr);
        printf("Valid move (0 move).\n");
        if (play[cardMovePos[0]][cardMovePos[1]] == deck[draw]) {
            deck[draw] = 0;
            for (i = 0; i <= 1; i++) {
                while (deck[draw] == 0) {
                    draw++;
                    if (draw == 53) {
                        draw = 29;
                        break;
                    }
                }
            }
        }
        return draw;

        // Catch all error if nothing else is working.
    } else {
        printf("Returning to menu.\n");
        sleep(3);
        return draw;
    }
}

int playerMoveDecision(int play[21][7], int hidden[19][7], int dropDeck[4], int deck[53],
                       int playerCardChoice[2], int playerMoveChoice[2], int draw) {
    int i, drawDeckChoice, deckPullChoice = 0;
    deckPullChoice = 0;
    if (deck[draw] != 0) {
        printf("Would you like to enter draw deck menu? (y=1, n=0) ");
        while (scanf("%d", &drawDeckChoice) != 1 || (drawDeckChoice != 1 && drawDeckChoice != 0)) {
            while (getchar() != '\n');
            printf("Error. Please input a 1 or 0: ");
        }
        if (drawDeckChoice == 1) {
            draw = deckPull(play, deck, playerCardChoice, draw, hidden, dropDeck, deckPullChoice);
            // printf("Draw number after exiting deckPull: %d", draw);
            if (play[20][6] == deck[draw]) {
                deckPullChoice = 1;
            }
        }
    }
    if (drawDeckChoice == 0) {
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
        return draw;
    }

    if (deckPullChoice == 1) {
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
    }

    /*
    //DEBUG
    printf("\nPlayer Card Position: [%d, %d]", playerCardChoice[0], playerCardChoice[1]);
    printf("\nPlayer Move Position: [%d, %d]", playerMoveChoice[0], playerMoveChoice[1]);
    printf("\nPlayer Choice: %d", play[playerCardChoice[0]][playerCardChoice[1]]);
    printf("\nPlayer Move: %d", play[playerMoveChoice[0]][playerMoveChoice[1]]);
    printf("\nPlayer Move Above: %d", play[playerMoveChoice[0] - 1][playerMoveChoice[1]]);
    printf("\nPlayer Move Above mod: %d", (play[playerMoveChoice[0] - 1][playerMoveChoice[1]] - 1) % 13);
    printf("\nPlayer Move Above mod - 1: %d", ((play[playerMoveChoice[0] - 1][playerMoveChoice[1]] - 1) % 13) - 1);
    printf("\nPlayer Choice mod: %d\n", (play[playerCardChoice[0]][playerCardChoice[1]] - 1) % 13);
    printf("Draw Value Before Exiting Function: %d\n", draw);
    //DEBUG
     */
    return draw;
}

int deckPull(int play[21][7], int deck[53], int cardPos[2], int draw, int hidden[21][7], int dropDeck[4],
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
                play[cardPos[0]][cardPos[1]] = deck[draw];
                break;
            case 2:
                printf("You have cycled the deck.\n");
                draw++;
                if (draw < 53) {
                    for (i = 0; i <= 1; i++) {
                        while (deck[draw] == 0) {
                            draw += 1;
                            if (draw == 53) {
                                draw = 29;
                                break;
                            }
                        }
                    }
                } else {
                    draw = 29;
                }
                frameGen(play, hidden, deck, dropDeck, draw);
                break;
            case 3:
                play[20][6] = 0;
                printf("You have reset to the start menu.\n");
                break;
        }
    } while (deckPullChoice == 2);
    return draw;
}