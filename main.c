#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "solFunc.h"
#include "gameLogic.h"

int main() {
    int yesNo, moveYesNo, game, draw;
    int deck[53], hidden[19][7], play[22][7], dropDeck[4];
    int playerCardChoice[2] = {0, 0}, playerMoveChoice[2] = {0, 0}, moveCount;
    int *moveptr = &moveCount, *drawptr = &draw;

    time_t t;
    srand(time(&t));
    do {
        system("clear");
        printf("Welcome to Solitaire! Would you like to play? (y=1, n=0) ");
        while (scanf("%d", &yesNo) != 1 || (yesNo != 1 && yesNo != 0)) {
            while (getchar() != '\n');
            printf("Error. Please input a 1 or 0: ");
        }
        if (yesNo == 0) {
            break;
        }

        game = 0; // Used to start a new game.
        *moveptr = 0; // Used to reset the move counter.
        *drawptr = 29; // Used to reset the draw pointer.

        // RESET FUNCTIONS:
        deckResetShuffle(deck);
        hiddenGen(hidden);
        playGen(play, deck);
        dropDeckReset(dropDeck);

        // GAME GOES HERE:
        while (game == 0) {
            // Reset variables every turn:
            playerCardChoice[0] = 0;
            playerCardChoice[1] = 0;
            playerMoveChoice[0] = 0;
            playerMoveChoice[1] = 0;
            // Generate frame:
            frameGen(play, hidden, deck, dropDeck, drawptr);
            // Player move:
            playerMoveDecision(play, hidden, dropDeck, deck, playerCardChoice, playerMoveChoice, drawptr, &game);
            cardMoveEval(play, hidden, playerCardChoice, playerMoveChoice, dropDeck, deck, drawptr, moveptr);
            // Check for win:
            if (dropDeck[0] == 13 && dropDeck[1] == 26 && dropDeck[2] == 39 && dropDeck[3] == 52) {
                frameGen(play, hidden, deck, dropDeck, drawptr);
                printf("\nCongratulations! You win! \nYou made %d move(s) to finish.\n\n", *moveptr);
                game = 3;
            }
        }
    } while (game == 1);
    switch (game) {
        case 2:
            mikeDisappointed();
            break;
        case 3:
            gigaChad();
            break;
    }
    return 0;
}