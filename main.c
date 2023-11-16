#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "solFunc.h"
#include "debugFunc.h"
#include "gameLogic.h"

int main() {
    int yesNo, game=0, inc=0;
    int deck[53], hidden[19][7], play[19][7];
    int dropDeck[4];
    int playerCardChoice[2], playerMoveChoice[2], i;
    time_t t;
    srand(time(&t));
    printf("Welcome to Solitaire! Would you like to play? (y=1, n=0) ");
    do {
        while (scanf("%d", &yesNo) != 1 || (yesNo != 1 && yesNo != 0)) {
            while (getchar() != '\n');
            printf("Error. Please input a 1 or 0: ");
        }
        if (yesNo == 0) {
            break;
        }
        // RESET FUNCTIONS:

        deckResetShuffle(deck);
        // deckPrint(Deck);
        hiddenGen(hidden);
        // hiddenPrint(Hidden);
        playGen(play, deck);
        // hiddenPrint(Play);
        dropDeckReset(dropDeck);

        // GAME GOES HERE:
        while(game == 0){
            frameGen(play, hidden, deck, dropDeck, inc);
            printf("Would you like to move a card? (y=1, n=0) ");
            while (scanf("%d", &yesNo) != 1 || (yesNo != 1 && yesNo != 0)) {
                while (getchar() != '\n');
                printf("Error. Please input a 1 or 0: ");
            }
            if (yesNo == 0) {
                break;
            } else { //Player Card Choice:
                printf("Please input the column you would like to select for a move: ");
                while (scanf("%d-1", &playerCardChoice[1]) != 1 || playerCardChoice[1] < 0 || playerCardChoice[1] > 6) {
                    while (getchar() != '\n');
                    printf("Error. Please input a number between 1 and 7: ");
                }
                printf("Please input the row of the card you would like to move: ");
                while (scanf("%d-1", &playerCardChoice[1]) != 1 || playerCardChoice[1] < 0 || playerCardChoice[1] > 18) {
                    while (getchar() != '\n');
                    printf("Error. Please input a number between 1 and 19: ");
                }
                printf("Please input the column you would like to move to: ");
                while (scanf("%d-1", &playerMoveChoice[1]) != 1 || playerMoveChoice[1] < 0 || playerMoveChoice[1] > 6) {
                    while (getchar() != '\n');
                    printf("Error. Please input a number between 1 and 7: ");
                }
                for (i = 18; i >= 0; i--) {
                    if (play[i][playerCardChoice[1]] != 0) {
                        playerCardChoice[1] = i;
                        break;
                    }
                }
            }
            cardMoveEval(play, hidden, playerCardChoice, playerMoveChoice);
            frameGen(play, hidden, deck, dropDeck, inc);
            break;
        }

        printf("Would you like to play again? (y=1,n=0) ");
    } while (yesNo == 1);
    system("clear");
    switch (rand()%2){
        case 0:
            gigaChad();
            break;
        case 1:
            mikeDisappointed();
            break;
    }
    return 0;
}