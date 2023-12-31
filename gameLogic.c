#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <malloc.h>
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
        printf("You must pick a card.\n");
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
            (*draw)++;
            for (i = 0; i <= 1; i++) {
                while (deck[*draw] == 0 || *draw >= 53) {
                    (*draw)++;
                    if (*draw >= 53) {
                        *draw = 29;
                        break;
                    }
                }
            }
            if (*draw >= 53) {
                *draw = 29;
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
            (*draw)++;
            for (i = 0; i <= 1; i++) {
                while (deck[*draw] == 0 || *draw >= 53) {
                    (*draw)++;
                    if (*draw >= 53) {
                        *draw = 29;
                        break;
                    }
                }
            }
            if (*draw >= 53) {
                *draw = 29;
            }
        }
        return;
    }   // If the move position is the top row, this ensures it is empty.
    else if (cardMovePos[0] == 0 && play[cardMovePos[0]][cardMovePos[1]] == 0) {
        cardMove(play, hidden, cardPos, cardMovePos, moveCount);
        printf("Valid move (0 move).\n");
        if (play[cardMovePos[0]][cardMovePos[1]] == deck[*draw]) {
            deck[*draw] = 0;
            (*draw)++;
            for (i = 0; i <= 1; i++) {
                while (deck[*draw] == 0 || *draw >= 53) {
                    (*draw)++;
                    if (*draw >= 53) {
                        *draw = 29;
                        break;
                    }
                }
            }
            if (*draw >= 53) {
                *draw = 29;
            }
        }
        return;
    } // Catch all error if nothing else is working.
    else {
        printf("Invalid. Returning to menu.\n");
        sleep(3);
        return;
    }
}

void playerMoveDecision(int play[22][7], int hidden[19][7], int dropDeck[4], int deck[53],
                        int playerCardChoice[2], int playerMoveChoice[2], int *draw, int *game) {
    int i;
    int correct = 0, drawSignal = 0;
    FILE* file;
    char ch; //used for printing from file

    while (correct == 0) { // Loop until a valid input is entered
        frameGen(play, hidden, deck, dropDeck, draw); // Display the game board

        printf("Enter your move (type 'h' for help): ");
        char *decisionArray = malloc(sizeof(char) * 6);
        if (decisionArray == NULL) {
            printf("Error allocating memory for decision matrix.\n");
            break;
        }
        for (i = 0; i < 6; i++) {
            decisionArray[i] = '\0';
        }

        fgets(decisionArray, 6, stdin); // Get user input

        // Check if the input is empty or newline only
        if (decisionArray[0] == '\n' || decisionArray[0] == '\0') {
            printf("No input detected, please enter a move.\n");
            free(decisionArray);
            continue; // Skip the rest of the loop and prompt for input again
        }
        /*
        printf("%c | %c | %c | %c\n", decisionArray[0], decisionArray[1], decisionArray[2],
               decisionArray[3]); // Debug output
        sleep(2);
        */
        // Check if the input is within the expected length
        if ((decisionArray[4] == '\n') || (decisionArray[4] == '\0')) {
            // Special handling for single-character commands
            if (decisionArray[1] == '\n') {
                if ((decisionArray[0] >= 67) && (decisionArray[0] <= 81)) {
                    tolower(decisionArray[0]); // Convert to lowercase
                }
                switch (decisionArray[0]) {
                    case 'c':
                        if (deck[*draw] == 0) {
                            printf("No more cards in stock\n");
                            sleep(2);
                            correct = 2;
                            break;
                        }
                        // Logic for cycling through the draw deck, skips blank cards
                        (*draw)++;
                        for (i = 0; i <= 1; i++) {
                            while (deck[*draw] == 0 || *draw >= 53) {
                                (*draw)++;
                                if (*draw >= 53) {
                                    *draw = 29;
                                    break;
                                }
                            }
                        }
                        if (*draw >= 53) {
                            *draw = 29;
                        }
                        correct = 3;
                        break;
                    case 'h':
                        file = fopen("help.txt","r");
                          if (file == NULL){
                            printf("Error. help.txt file is missing\n");
                          }
                          else {
                            while (!feof(file)) {
                              ch = fgetc(file);
                              printf("%c",ch);
                            }
                          }
                        fclose(file);
                        printf("Press Enter to Continue");
                        scanf("%c",&ch);
                        correct = 2; //exits while loop
                        break;
                    case 'q':
                        printf("Quit\n");
                        *game = 2; //game exits
                        correct = 2; //exits while loop
                        break;
                    case 'r':
                        printf("Reset\n");
                        *game = 1; //game resets
                        correct = 2; //exits while loop
                        break;
                }
                // Exits loop
                if (correct == 2) {
                    break;
                }
                // Repeats Loop to start after draw deck cycle
                if (correct == 3) {
                    continue;
                }
                // Column Input:
            } else if (decisionArray[0] >= '0' && decisionArray[0] <= '7') {
                switch (decisionArray[0]) {
                    case '1' ... '7':
                        playerCardChoice[1] = decisionArray[0] - 48; // Set the column of the card to move
                        break;
                    case '0':
                        playerCardChoice[1] = 7;
                        playerCardChoice[0] = 21;
                        play[20][6] = deck[*draw];
                        drawSignal = 1;
                        break;
                }
            } else {
                printf("Invalid move syntax (decisionMatrix[0]), invalid column input\n"); // Error for invalid first character (column number)
                sleep(2);
            }
            // Row input:
            // Checks for 4 number input for double-digit row input
            if (decisionArray[3] != '\n' && decisionArray[1] == '1' && decisionArray[2] >= '1' &&
                decisionArray[2] <= '9') {
                playerCardChoice[0] = 10 + decisionArray[2] - 48; // Adjust for 10-card selection (row)
            }   // Checks for 3 number input for single-digit row input
            else if (decisionArray[2] != '\n' && decisionArray[1] >= '1' && decisionArray[1] <= '9') {
                playerCardChoice[0] = decisionArray[1] - 48;          // Set row of the card to move
            }   //Checks if no row is selected, picking top-most card of input column
            else if (decisionArray[2] == '\n' && decisionArray[0] >= '0' && decisionArray[0] <= '7' && drawSignal != 1) {
                // Iterate through the column to find the topmost card
                for (i = 19; i > 0; i--) {
                    if (play[i-1][playerCardChoice[1]-1] != 0) {
                        playerCardChoice[0] = i; // Set the row of the topmost card to move
                        correct = 1;
                        break;
                    }
                }
            } else if (drawSignal == 1) {
            } else {
                printf("Invalid move syntax (decisionMatrix[1 or 2]), invalid row input\n");
                sleep(2);
            }
            // Move position input:
            // Handle draw deck input for move position
            if (decisionArray[0] == '0' && decisionArray[1] >= '1' && decisionArray[1] <= '8' &&
                decisionArray[2] == '\n' && correct == 0) {
                playerMoveChoice[1] = decisionArray[1] - 48; // Set target column for the move
                correct = 1;
            } else if (decisionArray[3] == '\n') {
                // Handle single digit row input
                if (decisionArray[2] >= '1' && decisionArray[2] <= '8') {
                    playerMoveChoice[1] = decisionArray[2] - 48; // Set target column for the move
                    correct = 1;
                } else {
                    printf("Invalid move syntax (decisionMatrix[2 or 3]), invalid move.\n");
                    sleep(2);
                }
            } else if (decisionArray[3] >= '0' && decisionArray[3] <= '8') {
                // Handle double digit row input
                if (decisionArray[3] >= '0' && decisionArray[3] <= '9') {
                    playerMoveChoice[1] = decisionArray[3] - 48; // Adjust for 10-card selection (row)
                    correct = 1;
                } else {
                    printf("Invalid move syntax (decisionMatrix[2 or 3]), invalid move.\n");
                    sleep(2);
                }
                // If no row was selected, this applies the move position.
            } else if (correct = 1 && decisionArray[1] >= '1' && decisionArray[1] <= '8') {
                playerMoveChoice[1] = decisionArray[1] - 48; // Set target column for the move
            } else {
                printf("Invalid move syntax (decisionMatrix[2 or 3]), invalid move.\n");
                sleep(2);
            }
        } else {
            printf("Invalid syntax, too many characters.\n"); // Error for invalid move syntax
            sleep(2);
        }
        free(decisionArray);
    }
    // Finalize the move if input is correct
    if (correct == 1) {
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
}