#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <wchar.h>
#include <locale.h>
#include "solFunc.h"

void hiddenGen(int HIDDEN[19][7]) {
    int count = 1, i, j;
    for (i = 0; i < 19; i++) {
        for (j = 0; j < 7; j++) {
            HIDDEN[i][j] = 0;
        }
    }
    for (i = 0; i < 6; i++) {
        for (j = 6; j >= count; j--) {
            HIDDEN[i][j] = 99;
        }
        count++;
    }
}

void playGen(int PLAY[19][7], int Deck[53]) {
    int count = 0, i, j, a = 1;
    for (i = 0; i < 19; i++) {
        for (j = 0; j < 7; j++) {
            PLAY[i][j] = 0;
        }
    }
    for (i = 0; i < 7; i++) {
        for (j = 6; j >= count; j--) {
            PLAY[i][j] = Deck[a];
            a++;
        }
        count++;
    }
}

void deckResetShuffle(int Deck[53]) {
    int x, count;
    for (x = 0; x < 53; x++) {
        Deck[x] = x;
    }
    for (count = 0; count <= 2; count++) {
        for (x = 51; x > 0; x--) {
            int r = rand() % x + 1;
            int temp = Deck[x];
            Deck[x] = Deck[r];
            Deck[r] = temp;
        }
    }
}

void frameGen(int play[19][7], int hidden[19][7], int deck[53], int inc) {
    int i, j;
    setlocale(LC_CTYPE, "");
    system("clear");
    // Print Draw Deck:
    printf("\033[0;30m\033[48;5;240m");  // Black text, grey background
    printf("Top of Draw Deck: ");
    numCardPrint(deck[inc+30]);
    printf("\033[0m"); // Reset text to default
    // Print Game Board:
    for (i = 0; i < 19; i++) {
        for (j = 0; j < 7; j++) {
            numCardPrint(play[i][j]);
            if(hidden[i][j] == 99){
                numCardPrint(hidden[i][j]);
            }
        }
    }
}

void numCardPrint(int card) {
    switch (card) {
        case 1 ... 13:
            printf("\033[0;31m\033[48;5;240m");  // Red text, grey background
            if (card % 13 == 0 || card % 13 > 10 || card % 13 == 1) {
                faceCardPrint(card);
            } else {
                printf(" %lc%2.d", 0x2665, card % 13); // Hearts
            }
            printf("\033[0m"); // Reset text to default
            break;
        case 14 ... 26:
            printf("\033[0;30m\033[48;5;240m");  // Black text, grey background
            if (card % 13 == 0 || card % 13 > 10 || card % 13 == 1) {
                faceCardPrint(card);
            } else {
                printf(" %lc%2.d", 0x2663, pcard % 13); // Clubs
            }
            printf("\033[0m"); // Reset text to default
            break;
        case 27 ... 39:
            printf("\033[0;31m\033[48;5;240m");  // Red text, grey background
            if (card % 13 == 0 || card % 13 > 10 || card % 13 == 1) {
                faceCardPrint(card);
            } else {
                printf(" %lc%2.d", 0x2666, card % 13); // Diamonds
            }
            printf("\033[0m"); // Reset text to default
            break;
        case 40 ... 52:
            printf("\033[0;30m\033[48;5;240m");  // Black text, grey background
            if (card % 13 == 0 || card % 13 > 10 || card % 13 == 1) {
                faceCardPrint(card);
            } else {
                printf(" %lc%2.d", 0x2660, card % 13); // Spades
            }
            printf("\033[0m"); // Reset text to default
            break;
        case 99:
            printf("\033[0;32m\033[48;5;240m");  // Green text, grey background
            printf(" XXX"); // Hidden card
            printf("\033[0m");
            break;
        default: {
            printf("\033[48;5;240m");
            printf("    ");
            printf("\033[0m");
            break;
        }
    }
}

void faceCardPrint(int card) {
    wchar_t suitSymbol;
    char faceChar;

    if (card >= 1 && card <= 13) {
        suitSymbol = 0x2665; // Hearts
    } else if (card >= 14 && card <= 26) {
        suitSymbol = 0x2663; // Clubs
    } else if (card >= 27 && card <= 39) {
        suitSymbol = 0x2666; // Diamonds
    } else if (card >= 40 && card <= 52) {
        suitSymbol = 0x2660; // Spades
    }

    switch (card % 13) {
        case 0:             // Card 13 evaluates as 0, in *deck array 13 is King.
            faceChar = 'K';
            break;
        case 11:
            faceChar = 'J';
            break;
        case 12:
            faceChar = 'Q';
            break;
        case 1:
            faceChar = 'A';
            break;
    }
    printf(" %lc %c", suitSymbol, faceChar);
}