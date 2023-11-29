#include <stdio.h>
#include <unistd.h>
#include "solFunc.h"
#include "gameLogic.h"

void cardMove(int play[19][7], int hidden[19][7], int cardPos[2], int cardMovePos[2], int *moveCount) {
    int i;
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
}

void cardMoveDrop(int play[19][7], int hidden[19][7], int cardPos[2], int dropDeck[4], int *moveCount) {
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
}


void cardMoveEval(int play[19][7], int hidden[19][7], int cardPos[2], int cardMovePos[2], int dropDeck[4], int deck[53],
                  int *draw, int *moveCount) {
    int i;
    // This checks if the card is hidden.
    if (hidden[cardPos[0]][cardPos[1]] == 99) {
        printf("Error. You cannot choose a hidden card.\n");
        sleep(3);
        return;
    }   // Resets due to exit condition flag in playerMoveDecision.
    else if (cardPos[0] == 0 && cardPos[1] == 0 && cardMovePos[0] == 0 && cardMovePos[1] == 0) {
        return;
    }   // This checks if the card selected is not empty.
    else if (play[cardPos[0]][cardPos[1]] == 0) {
        printf("Returning to menu.\n");
        sleep(3);
        return;
    }   // Drop Deck evaluation
    else if (cardMovePos[1] == 7) {
        if (play[cardPos[0] + 1][cardPos[1]] != 0) {
            printf("Invalid Selection. Your card must be singular and not in a stack for the drop deck.\n");
            sleep(3);
        } else {
            switch (play[cardPos[0]][cardPos[1]]) {
                case 1 ... 13 :
                    if (play[cardPos[0]][cardPos[1]] % 13 == dropDeck[0] % 13 + 1 ||
                        play[cardPos[0]][cardPos[1]] == 13) {
                        cardMoveDrop(play, hidden, cardPos, dropDeck, moveCount);
                        printf("Valid move.\n");
                    } else {
                        printf("Invalid move. Please Select Valid Card for Hearts Drop Deck.\n");
                        sleep(3);
                    }
                    break;
                case 14 ... 26 :
                    if (play[cardPos[0]][cardPos[1]] % 13 == dropDeck[1] % 13 + 1 ||
                        play[cardPos[0]][cardPos[1]] == 26) {
                        cardMoveDrop(play, hidden, cardPos, dropDeck, moveCount);
                        printf("Valid move.\n");
                    } else {
                        printf("Invalid move. Please Select Valid Card for Clubs Drop Deck.\n");
                        sleep(3);
                    }
                    break;
                case 27 ... 39 :
                    if (play[cardPos[0]][cardPos[1]] % 13 == dropDeck[2] % 13 + 1 ||
                        play[cardPos[0]][cardPos[1]] == 39) {
                        cardMoveDrop(play, hidden, cardPos, dropDeck, moveCount);
                        printf("Valid move.\n");
                    } else {
                        printf("Invalid move. Please Select Valid Card for Diamonds Drop Deck.\n");
                        sleep(3);
                    }
                    break;
                case 40 ... 52 :
                    if (play[cardPos[0]][cardPos[1]] % 13 == dropDeck[3] % 13 + 1 ||
                        play[cardPos[0]][cardPos[1]] == 52) {
                        cardMoveDrop(play, hidden, cardPos, dropDeck, moveCount);
                        printf("Valid move.\n");
                    } else {
                        printf("Invalid move. Please Select Valid Card for Hearts Drop Deck.\n");
                        sleep(3);
                    }
                    break;
            }
        }   // Update draw deck based on dropDeck
        if (dropDeck[0] == deck[*draw] || dropDeck[1] == deck[*draw] || dropDeck[2] == deck[*draw] ||
            dropDeck[3] == deck[*draw]) {
            deck[*draw] = 0;
            for (i = 0; i <= 1; i++) {
                while (deck[*draw] == 0) {
                    (*draw)++;
                    if (*draw == 53) {
                        *draw = 29;
                        break;
                    }
                }
            }
        }
        return;
    }   // The following check is to ensure the card is one value lower, opposite suit for a valid move.
    else if ((play[cardPos[0]][cardPos[1]] - 1) % 13 == ((play[cardMovePos[0] - 1][cardMovePos[1]] - 1) % 13 - 1) &&
             (((play[cardPos[0]][cardPos[1]] >= 1 && play[cardPos[0]][cardPos[1]] <= 13) ||
               (play[cardPos[0]][cardPos[1]] >= 27 && play[cardPos[0]][cardPos[1]] <= 39)) !=
              ((play[cardMovePos[0] - 1][cardMovePos[1]] >= 1 && play[cardMovePos[0] - 1][cardMovePos[1]] <= 13) ||
               (play[cardMovePos[0] - 1][cardMovePos[1]] >= 27 && play[cardMovePos[0] - 1][cardMovePos[1]] <= 39)))) {
        cardMove(play, hidden, cardPos, cardMovePos, moveCount);
        printf("Valid move (Normal Move).\n");
        if (play[cardMovePos[0]][cardMovePos[1]] == deck[*draw]) {
            deck[*draw] = 0;
            for (i = 0; i <= 1; i++) {
                while (deck[*draw] == 0) {
                    (*draw)++;
                    if (*draw == 53) {
                        *draw = 29;
                        break;
                    }
                }
            }
        }
        return;
    }   // If the move position is the top row, this ensures it is empty.
    else if (cardMovePos[0] == 0 && play[cardMovePos[0]][cardMovePos[1]] == 0) {
        cardMove(play, hidden, cardPos, cardMovePos, moveCount);
        printf("Valid move (0 move).\n");
        if (play[cardMovePos[0]][cardMovePos[1]] == deck[*draw]) {
            deck[*draw] = 0;
            for (i = 0; i <= 1; i++) {
                while (deck[*draw] == 0) {
                    (*draw)++;
                    if (*draw == 53) {
                        *draw = 29;
                        break;
                    }
                }
            }
        }
        return;
    } // Catch all error if nothing else is working.
    else {
        printf("Returning to menu.\n");
        sleep(3);
        return;
    }
}

void playerMoveDecision(int play[21][7], int hidden[19][7], int dropDeck[4], int deck[53],
                        int playerCardChoice[2], int playerMoveChoice[2], int *draw) {
    int i;
    char decisionArray[6]; // Main array to store user input
    int correct = 0; // Flag to check if a valid input is entered

    while (correct == 0) { // Loop until a valid input is entered
        for (i = 0; i < 6; i++) {
            decisionArray[i] = '\0'; // Initialize decision array with NULLs each loop iteration
        }

        printf("Enter your move: ");
        fgets(decisionArray, 6, stdin); // Get user input

        // Check if input is longer than expected, triggering cleanup if so
        if ((decisionArray[4] != '\0' && decisionArray[4] != '\n')) {
            while (getchar() != '\n'); // Clean up overflowed chars
        }

        printf("%c | %c | %c | %c\n", decisionArray[0], decisionArray[1], decisionArray[2],
               decisionArray[3]); // Debug output

        // Check if the input is within the expected length
        if ((decisionArray[4] == '\n') || (decisionArray[4] == '\0')) {
            // Special handling for single-character commands
            if (decisionArray[1] == '\n') {
                if ((decisionArray[0] >= 67) && (decisionArray[0] <= 81)) {
                    decisionArray[0] = decisionArray[0] + 32; // Convert to lowercase
                }
                switch (decisionArray[0]) {
                    case 'c':
                        if (deck[*draw] == 0) {
                            printf("No more cards in stock\n");
                            sleep(2);
                            correct = 2;
                            break;
                        }
                        // Logic for cycling through the draw deck
                        if (*draw < 53) {
                            for (i = 0; i <= 1; i++) {
                                while (deck[*draw] == 0) {
                                    (*draw)++;
                                    if (*draw == 53) {
                                        *draw = 29;
                                        break;
                                    }
                                }
                            }
                        } else {
                            *draw = 29;
                        }
                        frameGen(play, hidden, deck, dropDeck, draw);
                        break;
                    case 'h':
                        printf("Help\n");
                        correct = 2; //exits while loop
                        break;
                    case 'q':
                        printf("Quit\n");
                        correct = 2; //exits while loop
                        break;
                }
                if (correct == 2) {
                    break;
                }
            } else if ((decisionArray[0] >= '0') && (decisionArray[0] <= '7')) {
                switch (decisionArray[0]) {
                    case '1' ... '7':
                        playerCardChoice[1] = decisionArray[0] - 48; // Set the column of the card to move
                        break;
                    case '0':
                        playerCardChoice[0] = 20;
                        playerCardChoice[1] = 6;
                        play[20][6] = deck[*draw];
                        break;
                }
            } else {
                printf("Invalid move syntax (decisionMatrix[0]), invalid column input\n"); // Error for invalid first character (column number)
                break;
            }
            // Checks for 3 number input for single-digit row input
            if (decisionArray[3] != '\n') {
                if (decisionArray[1] == '1' && decisionArray[2] >= '0' && decisionArray[2] <= '9') {
                    playerCardChoice[0] = 10 + decisionArray[2] - 48; // Adjust for 10-card selection (row)
                }
            } else if (decisionArray[0] = '0' && decisionArray[1] >= '1' && decisionArray[1] <= '8') {
                playerMoveChoice[1] = decisionArray[1] - 48;          // Set row of the card to move to
                correct = 1;
                break;
            }
                // Checks for single digit column input instead
            else if (decisionArray[1] >= '0' && decisionArray[1] <= '9') {
                playerCardChoice[0] = decisionArray[1] - 48;          // Set row of the card to move
                correct = 1; // Set flag for valid input
            } else {
                printf("Invalid move syntax (decisionMatrix[1 or 2]), invalid row input\n");
                break;
            }
            // Check if the row is single-digit for move choice location in array
            if (decisionArray[3] == '\n') {
                if (decisionArray[2] >= '1' && decisionArray[2] <= '8') {
                    playerMoveChoice[1] = decisionArray[2] - 48; // Set target column for the move
                } else {
                    printf("Invalid move syntax (decisionMatrix[2]), invalid move.\n"); // Error for invalid move syntax
                    break;
                }
            }   // Check if the row is double-digit for move choice location in array
            else if (decisionArray[3] >= '1' && decisionArray[3] <= '8') {
                playerMoveChoice[1] = decisionArray[3] - 48; // Set target column for the move
                correct = 1; // Set flag for valid input
            } else {
                printf("Invalid move syntax (decisionMatrix[3]), invalid move.\n"); // Error for invalid move syntax
                break;
            }
        } else {
            printf("Invalid syntax, too many characters.\n"); // Error for invalid move syntax
            break;
        }
    }
    // Finalize the move if input is correct
    if (correct == 1) {
        playerCardChoice[0]--;
        playerCardChoice[1]--;
        playerMoveChoice[1]--;
        for (i = 19; i > 0; i--) {
            playerMoveChoice[0] = i - 1;
            if (play[playerMoveChoice[0]][playerMoveChoice[1]] != 0) {
                playerMoveChoice[0] =
                        i;
                break;
            }
        }
    }
/*
int i, drawDeckChoice = 0, deckPullChoice = 0;
if (deck[*draw] != 0) {
    printf("Would you like to enter draw deck menu? (y=1, n=0) ");
    while (scanf("%d", &drawDeckChoice) != 1 || (drawDeckChoice != 1 && drawDeckChoice != 0)) {
        while (getchar() != '\n');
        printf("Error. Please input a 1 or 0: ");
    }
    if (drawDeckChoice == 1) {
        deckPull(play, deck, playerCardChoice, draw, hidden, dropDeck, deckPullChoice);
        // printf("Draw number after exiting deckPull: %d", *draw);
        if (play[20][6] == deck[*draw]) {
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
    while (scanf("%d", &playerMoveChoice[1]) != 1 || playerMoveChoice[1] < 1 || playerMoveChoice[1] > 8) {
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
}

if (deckPullChoice == 1) {
    printf("Please input the column you would like to move to (1-8), 8 is for drop deck: ");
    while (scanf("%d", &playerMoveChoice[1]) != 1 || playerMoveChoice[1] < 1 || playerMoveChoice[1] > 8) {
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

// DEBUG:
/*
printf("\nPlayer Card Position: [%d, %d]", playerCardChoice[0], playerCardChoice[1]);
printf("\nPlayer Move Position: [%d, %d]", playerMoveChoice[0], playerMoveChoice[1]);
printf("\nPlayer Choice: %d", play[playerCardChoice[0]][playerCardChoice[1]]);
printf("\nPlayer Move: %d", play[playerMoveChoice[0]][playerMoveChoice[1]]);
printf("\nPlayer Move Above: %d", play[playerMoveChoice[0] - 1][playerMoveChoice[1]]);
printf("\nPlayer Move Above mod: %d", (play[playerMoveChoice[0] - 1][playerMoveChoice[1]] - 1) % 13);
printf("\nPlayer Move Above mod - 1: %d", ((play[playerMoveChoice[0] - 1][playerMoveChoice[1]] - 1) % 13) - 1);
printf("\nPlayer Choice mod: %d\n", (play[playerCardChoice[0]][playerCardChoice[1]] - 1) % 13);
printf("Draw Value Before Exiting Function: %d\n", *draw);
*/
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
                break;
            case 2:
                printf("You have cycled the deck.\n");
                (*draw)++;
                if (*draw < 53) {
                    for (i = 0; i <= 2; i++) {
                        while (deck[*draw] == 0) {
                            (*draw)++;
                            if (*draw == 53) {
                                *draw = 29;
                                break;
                            }
                        }
                    }
                } else {
                    *draw = 29;
                }
                frameGen(play, hidden, deck, dropDeck, draw);
                break;
            case 3:
                play[20][6] = 0;
                printf("You have reset to the start menu.\n");
                break;
        }
    } while (deckPullChoice == 2);
}
