#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "solFunc.h"
#include "gameLogic.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "solFunc.h"
#include "gameLogic.h"

int main() {
    int yesNo, moveYesNo, game = 0, draw = 29;
    int deck[53], hidden[19][7], play[22][7], dropDeck[4];
    int playerCardChoice[2], playerMoveChoice[2], i, j, moveCount = 0;
    int *moveptr = &moveCount, *drawptr = &draw;

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

        game = 0; // Used to start a new game.

        // RESET FUNCTIONS:
        deckResetShuffle(deck, drawptr); // Assuming deckResetShuffle() is now void
        hiddenGen(hidden);
        playGen(play, deck);
        dropDeckReset(dropDeck);

        // GAME GOES HERE:
        while (game == 0) {
            frameGen(play, hidden, deck, dropDeck, drawptr);
            printf("Would you like to move a card? (y=1, n=0) ");
            while (scanf("%d", &moveYesNo) != 1 || (moveYesNo != 1 && moveYesNo != 0)) {
                while (getchar() != '\n');
                printf("Error. Please input a 1 or 0: ");
            }
            while (getchar() != '\n');
            if (moveYesNo == 0) {
                break;
            } else {
                playerMoveDecision(play, hidden, dropDeck, deck, playerCardChoice, playerMoveChoice, drawptr);
                cardMoveEval(play, hidden, playerCardChoice, playerMoveChoice, dropDeck, deck, drawptr, moveptr);
            }
            if (dropDeck[0] == 13 && dropDeck[1] == 26 && dropDeck[2] == 39 && dropDeck[3] == 52) {
                frameGen(play, hidden, deck, dropDeck, drawptr);
                printf("\nCongratulations! You win! \nYou made %d moves.\n", *moveptr);
                game = 1;
            }
        }
    } while (yesNo != 0);

    printf("Thank you for playing!\n");
    return 0;
}