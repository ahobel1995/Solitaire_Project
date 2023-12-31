/*
 * Project Title: Solitaire
 * Authors: Adrien Hobelman and Levi Campbell
 * Date: 11/28/2023 (finished)
 * Description: This program is a text-based version of the card game Solitaire. It uses a 2D array to represent the
 *             game board, and a 1D array to represent the deck. The game board is printed to the screen using ASCII
 *             characters. The game board is made up of 4 sections: the tableau, the hidden array, the stock, and the
 *             foundation. The tableau is a 2D array that holds the cards that are currently in play. The hidden array
 *             is a 2D array that masks the cards that are currently hidden. The stock is a 1D array that holds the
 *             cards that are currently read to draw. The foundation is a 1D 4 value array that holds the cards that
 *             have been collected. Once the foundation is full, the game is won. The game is lost when there are no
 *             more moves to be made, and the foundation is incomplete.
 * Resources:   ChatGPT, For assistance with bug-fixing and general help with the project (to include using pointers
 *             appropriately).
 *              Wikipedia, For assistance with the Fisher-Yates shuffle algorithm.
 *              Github Copilot, For assistance with rapid development of the project, by giving inline suggestions
 *             for writing longer more mundane lines of code. It saved time.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "solFunc.h"
#include "gameLogic.h"

int main() {
    int yesNo, game, draw;
    int deck[53], hidden[19][7], play[22][7], dropDeck[4];
    int playerCardChoice[2] = {0, 0}, playerMoveChoice[2] = {0, 0}, moveCount;
    int *moveptr = &moveCount, *drawptr = &draw;

    time_t t;
    srand(time(&t));
    system("clear");
    printf("Welcome to Solitaire! Would you like to play? (y=1, n=0) ");
    while (scanf("%d", &yesNo) != 1 || (yesNo != 1 && yesNo != 0)) {
        while (getchar() != '\n');
        printf("Error. Please input a 1 or 0: ");
    }
    while (getchar() != '\n' && getchar() != EOF);

    do {
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
                game = 3;
            }
        }
    } while (game == 1);
    switch (game) {
        case 2:
            mikeDisappointed();
            printf("\nYou lost in %d move(s)!\n\n", *moveptr);
            break;
        case 3:
            gigaChad();
            printf("\nCongratulations! You win! \nYou made %d move(s) to finish.\n\n", *moveptr);
            break;
    }
    return 0;
}