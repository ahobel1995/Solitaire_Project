#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <wchar.h>
#include <locale.h>
#include "solFunc.h"
#include "gameLogic.h"

void dropDeckReset(int dropDeck[4]) {
    int i;
    for (i = 0; i < 4; i++) {
        dropDeck[i] = 0;
    }
}

void hiddenGen(int hidden[19][7]) {
    int count = 1, i, j;
    for (i = 0; i < 19; i++) {
        for (j = 0; j < 7; j++) {
            hidden[i][j] = 0;
        }
    }
    for (i = 0; i < 6; i++) {
        for (j = 6; j >= count; j--) {
            hidden[i][j] = 99;
        }
        count++;
    }
}

void playGen(int play[22][7], int deck[53]) {
    int count = 0, i, j, a = 1;
    for (i = 0; i < 22; i++) {
        for (j = 0; j < 7; j++) {
            play[i][j] = 0;
        }
    }
    for (i = 0; i < 7; i++) {
        for (j = 6; j >= count; j--) {
            play[i][j] = deck[a];
            a++;
        }
        count++;
    }
}

void deckResetShuffle(int deck[53], int *draw) {
    int x, count;
    for (x = 0; x < 53; x++) {
        deck[x] = x;
    }
    for (count = 0; count <= 2; count++) {
        for (x = 51; x > 0; x--) {
            int r = rand() % x + 1;
            int temp = deck[x];
            deck[x] = deck[r];
            deck[r] = temp;
        }
    }
    *draw = 29;
}

void frameGen(int play[21][7], int hidden[21][7], int deck[53], int dropDeck[4], int* draw) {
    int i, j;
    setlocale(LC_CTYPE, "");
    system("clear");

    // Print Draw Deck:
    printf("       ");
    printf("\033[0;30m\033[48;5;240m");  // Black text, grey background
    printf("Top of Draw Deck:   ");
    numCardPrint(deck[*draw]);
    printf("\033[0;30m\033[48;5;240m");  // Black text, grey background
    printf("    ");
    printf("\033[0m"); // Reset text to default

    // Print Drop Decks:
    printf("\n       ");
    printf("\033[0;30m\033[48;5;240m"); // Black text, grey background
    printf("Drop Decks: ");
    for(i=0; i<4; i++){
        numCardPrint(dropDeck[i]);
    }
    printf("                \n");
    // For style to match length of horizontal lines:
    printf("       ");
    printf("\033[0;30m\033[48;5;240m"); // Black text, grey background
    printf("                            ");
    printf("\033[0m"); // Reset text to default

    // Print Game Board:
    for (i = 0; i <= 19; i++) {
        printf("\n     %2.d", i);
        for (j = 0; j < 7; j++) {
            if (i == 0) {
                printf("\033[0;30m\033[48;5;240m"); // Black text, grey background
                printf("  %2.d", j + 1);
                printf("\033[0m"); // Reset text to default
            } else if (hidden[i-1][j] == 99){
                numCardPrint(hidden[i-1][j]);
            } else {
                numCardPrint(play[i-1][j]);
            }
        }
        printf("%2.d", i);
    }
    printf("\n\n");
    //DEBUG:
    /*
    for (i = 0; i <= 3; i++) {
        for (j = 1; j <= 13; j++) {
            printf("%2.d ", deck[i * 13 + j]);
        }
        printf("\n");
    }
    printf("draw: %d\ndeck draw: %d\n", draw, deck[draw]);
     */
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
                printf(" %lc%2.d", 0x2663, card % 13); // Clubs
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
        case 0:             // Card 13 % 13 evaluates as 0, in deck array 13 is King.
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

void gigaChad(){
    printf("⠀⠀⠘⡀⠀⠀⠀⠀Thanks for playing⠀⠀⠀⡜⠀⠀⠀\n"
           "⠀⠀⠀⠑⡀⠀⠀⠀⠀you gigaChad⠀⠀⠀⠀⠀⠀⡔⠁⠀⠀⠀\n"
           "⠀⠀⠀⠀⠈⠢⢄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⠴⠊⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠀⢸⠀⠀⠀⢀⣀⣀⣀⣀⣀⡀⠤⠄⠒⠈⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠀⠘⣀⠄⠊⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "\n"
           "⣿⣿⣿⣿⣿⣿⣿⣿⡿⠿⠛⠛⠛⠋⠉⠈⠉⠉⠉⠉⠛⠻⢿⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⡿⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠛⢿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⡏⣀⠀⠀⠀⠀⠀⠀⠀⣀⣤⣤⣤⣄⡀⠀⠀⠀⠀⠀⠀⠀⠙⢿⣿⣿\n"
           "⣿⣿⣿⢏⣴⣿⣷⠀⠀⠀⠀⠀⢾⣿⣿⣿⣿⣿⣿⡆⠀⠀⠀⠀⠀⠀⠀⠈⣿⣿\n"
           "⣿⣿⣟⣾⣿⡟⠁⠀⠀⠀⠀⠀⢀⣾⣿⣿⣿⣿⣿⣷⢢⠀⠀⠀⠀⠀⠀⠀⢸⣿\n"
           "⣿⣿⣿⣿⣟⠀⡴⠄⠀⠀⠀⠀⠀⠀⠙⠻⣿⣿⣿⣿⣷⣄⠀⠀⠀⠀⠀⠀⠀⣿\n"
           "⣿⣿⣿⠟⠻⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠶⢴⣿⣿⣿⣿⣿⣧⠀⠀⠀⠀⠀⠀⣿\n"
           "⣿⣁⡀⠀⠀⢰⢠⣦⠀⠀⠀⠀⠀⠀⠀⠀⢀⣼⣿⣿⣿⣿⣿⡄⠀⣴⣶⣿⡄⣿\n"
           "⣿⡋⠀⠀⠀⠎⢸⣿⡆⠀⠀⠀⠀⠀⠀⣴⣿⣿⣿⣿⣿⣿⣿⠗⢘⣿⣟⠛⠿⣼\n"
           "⣿⣿⠋⢀⡌⢰⣿⡿⢿⡀⠀⠀⠀⠀⠀⠙⠿⣿⣿⣿⣿⣿⡇⠀⢸⣿⣿⣧⢀⣼\n"
           "⣿⣿⣷⢻⠄⠘⠛⠋⠛⠃⠀⠀⠀⠀⠀⢿⣧⠈⠉⠙⠛⠋⠀⠀⠀⣿⣿⣿⣿⣿\n"
           "⣿⣿⣧⠀⠈⢸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠟⠀⠀⠀⠀⢀⢃⠀⠀⢸⣿⣿⣿⣿\n"
           "⣿⣿⡿⠀⠴⢗⣠⣤⣴⡶⠶⠖⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⡸⠀⣿⣿⣿⣿\n"
           "⣿⣿⣿⡀⢠⣾⣿⠏⠀⠠⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠛⠉⠀⣿⣿⣿⣿\n"
           "⣿⣿⣿⣧⠈⢹⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⡄⠈⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣴⣾⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣧⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣦⣄⣀⣀⣀⣀⠀⠀⠀⠀⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⡄⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⠀⠀⠀⠙⣿⣿⡟⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠇⠀⠁⠀⠀⠹⣿⠃⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⣿⡿⠛⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⢐⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⠿⠛⠉⠉⠁⠀⢻⣿⡇⠀⠀⠀⠀⠀⠀⢀⠈⣿⣿⡿⠉⠛⠛⠛⠉⠉\n"
           "⣿⡿⠋⠁⠀⠀⢀⣀⣠⡴⣸⣿⣇⡄⠀⠀⠀⠀⢀⡿⠄⠙⠛⠀⣀⣠⣤⣤⠄⠀\n");
}

void mikeDisappointed(){
    printf("               You Lost...\n"
           "                     Mike is Disappointed...\n"
           "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⣿⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢾⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠏⠃⠀⠀⣀⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠋⠆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⣶⣿⣿⣿⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣿⣿⣿⣿⣿⣿⡟⠀⠀⢀⡀⠀⠀⠀⠀⠀⣀⣀⣀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⣿⣿⣿⣿⣿⣿⣿⠷⠛⣫⣭⡉⠉⠲⣾⡿⠋⠉⣩⣭⣍⠛⢶⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣼⣿⣿⣿⣿⣿⣿⣿⡇⠀⢸⣿⣿⣿⠀⠀⠟⠧⠀⠸⣿⣿⣿⠀⠈⠛⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠀⠀⣠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⡀⠉⠋⠁⣠⣆⣀⣀⣠⣄⠉⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠀⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠁⢈⣽⣿⣿⣿⣿⣿⣿⣿⣿⣿⣏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⢀⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⢀⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡄⠈⠉⠛⠻⠿⢿⣿⡿⠟⠛⠛⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⣸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⠀⠀⠀⠀\n"
           "⠀⠀⠀⢰⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡼⠀⠀⠀⠀\n"
           "⠀⠀⠀⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠟⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡇⡇⠀⠀⠀\n"
           "⠀⠀⣸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣏⠀⢀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣴⣿⠁⢃⠀⠀⠀\n"
           "⠀⠀⣿⣿⣿⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠻⠿⠛⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⣿⣿⣿⣿⡇⢸⠀⠀⠀\n"
           "⠀⢸⣿⣿⡇⠈⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣶⣶⣦⣤⣄⣀⡀⠀⠀⠀⠀⠀⠀⣀⣤⡄⠀⠀⠀⠀⠀⣸⣿⣿⣿⣿⢿⣷⢸⡀⠀⠀\n"
           "⠀⣼⣿⣿⠀⠀⠹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠃⠀⠀⠀⠀⣠⣿⣿⣿⣿⠃⠀⣿⡏⡇⠀⠀\n"
           "⠀⣿⣿⡇⠀⠀⠀⠘⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⣀⣀⣤⣶⣿⣿⣿⠟⠁⠀⠀⠉⠁⡇⠀⠀\n"
           "⠀⡿⠛⠃⠀⠀⠀⠀⠀⠛⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠋⠀⠀⠀⠀⠀⠀⡇⠀⠀\n"
           "⠀⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⠉⠀⠀⠀⠀⠀⠀⡀⠀⡇⠀⠀\n"
           "⠀⣧⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⡟⠛⠿⠿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠁⠀⠀⠀⠀⠀⠀⠀⠀⢠⠀⡇⠀⠀\n"
           "⠀⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⠁⠀⠀⠀⠀⠀⠀⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠁⠀⠀⠀⢹⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠀⣷⠀⠀\n"
           "⠀⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⡏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠀⣿⠀⠀\n"
           "⠀⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠈⠀⢹⡄⠀\n"
           "⢠⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠻⡀\n"
           "⢸⣿⠀⠀⡀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣣\n"
           "⣾⣿⠀⠀⢹⡀⠀⠀⠀⠀⠀⠀⠀⠀⣇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡇⠀⢀⣿\n"
           "⢿⢿⡄⠀⠀⠳⡀⠀⠀⠀⠀⠀⠀⠀⣿⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⡄⠁⠀⣾⡟\n"
           "⠸⡈⢧⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢿⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⡿⠁\n"
           "⠀⠑⢌⣷⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠘⠛⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⣿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠴⠞⠉⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠀⠀⠀⣾⠃⠀⠀⣶⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⠀⠀⢠⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠀⣤⡴⠋⠀⢀⣠⢿⡇⠀⣀⠔⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⠀⠀⢸⣿⠀⠀⠀⠻⣀⣀⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠁⠀⠀⠀⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠢⠀⠸⠛⠓⠢⠄⠀⠉⠉⠁⠀⠀⠀⠀⠀⠀\n");
}