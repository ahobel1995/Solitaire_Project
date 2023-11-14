#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <wchar.h>
#include <locale.h>
#include "solFunc.h"

void hiddenGen(int HIDDEN[19][7]) {
    int count=1, i, j;
    for (i=0; i<19; i++) {
        for (j=0; j<7; j++) {
            HIDDEN[i][j] = 0;
        }
    }
    for (i=0; i<6; i++) {
        for (j = 6; j>=count; j--) {
            HIDDEN[i][j] = 99;
        }
        count++;
    }
}

void playGen(int PLAY[19][7], int Deck[53]) {
    int count=0, i, j, a=1;
    for (i=0; i<19; i++) {
        for (j=0; j<7; j++) {
            PLAY[i][j] = 0;
        }
    }
    for (i=0; i<7; i++) {
        for (j=6; j>=count; j--) {
            PLAY[i][j] = Deck[a];
            a++;
        }
        count++;
    }
}

void deckResetShuffle(int Deck[53]){
    int x, count;
    for(x=0; x<53; x++){
        Deck[x] = x;
    }
    for (count = 0; count <= 2; count++){
        for(x=51; x>0; x--) {
            int r = rand() % x + 1;
            int temp = Deck[x];
            Deck[x] = Deck[r];
            Deck[r] = temp;
        }
    }
}

void frameGen(int play[19][7], int hidden[19][7]){
    int i, j;
    setlocale(LC_CTYPE, "");
    system("clear");
    for(i=0; i<19; i++){
        for(j=0; j<7; j++){
            if (hidden[i][j] == 99){
                printf("\033[0;32m\033[48;5;240m");  // Grey background
                printf(" XXX");
                printf("\033[0m");
            } else {
                switch (play[i][j]) {
                    case 1 ... 13: {
                        printf("\033[0;31m\033[48;5;240m");  // Red text, grey background
                        if (((play[i][j]-1)%13)+1 > 10){
                            faceCardPrint(play[i][j]);
                        } else if (play[i][j]%13 == 1){
                            printf(" %lc%s", 0x2665, " A");
                        } else {
                            printf(" %lc%2.d", 0x2665, play[i][j]); // Hearts
                        }
                        printf("\033[0m"); // Reset text to default
                        break;
                    }
                    case 14 ... 26: {
                        printf("\033[0;30m\033[48;5;240m");  // Black text, grey background
                        if (((play[i][j]-1)%13)+1 > 10){
                            faceCardPrint(play[i][j]);
                        } else if (play[i][j]%13 == 1){
                            printf(" %lc%s", 0x2663, " A");
                        } else {
                            printf(" %lc%2.d", 0x2663, play[i][j]); // Clubs
                        }
                        printf("\033[0m"); // Reset text to default
                        break;
                    }
                    case 27 ... 39: {
                        printf("\033[0;31m\033[48;5;240m");  // Red text, grey background
                        if (((play[i][j]-1)%13)+1 > 10){
                            faceCardPrint(play[i][j]);
                        } else if (play[i][j]%13 == 1){
                            printf(" %lc%s", 0x2666, " A");
                        } else {
                            printf(" %lc%2.d", 0x2666, play[i][j]); // Diamonds
                        }
                        printf("\033[0m"); // Reset text to default
                        break;
                    }
                    case 40 ... 52: {
                        printf("\033[0;30m\033[48;5;240m");  // Black text, grey background
                        if (((play[i][j]-1)%13)+1 > 10){
                            faceCardPrint(play[i][j]);
                        } else if (play[i][j]%13 == 1){
                            printf(" %lc%s", 0x2660, " A");
                        } else {
                            printf(" %lc%2.d", 0x2660, play[i][j]); // Spades
                        }
                        printf("\033[0m"); // Reset text to default
                        break;
                    }
                    default: {
                        printf("\033[48;5;240m");
                        printf("    ");
                        printf("\033[0m");
                        break;
                    }
                }
            }
        }
        printf("\n");
    }
}

void faceCardPrint(int card){
    switch(card){
        case 1 ... 13: {
            switch(card%13){
                case 11: {
                    printf(" %lc %c", 0x2665, "J");
                    break;
                }
                case 12: {
                    printf(" %lc %c", 0x2665, "Q");
                    break;
                }
                case 13: {
                    printf(" %lc %c", 0x2665, "K");
                    break;
                }
            }
            break;
        }
        case 14 ... 26: {
            switch(card%13){
                case 11: {
                    printf(" %lc %c", 0x2663, "J");
                    break;
                }
                case 12: {
                    printf(" %lc %c", 0x2663, "Q");
                    break;
                }
                case 13: {
                    printf(" %lc %c", 0x2663, "K");
                    break;
                }
            }
            break;
        }
        case 27 ... 39: {
            switch(card%13){
                case 11: {
                    printf(" %lc %c", 0x2666, "J");
                    break;
                }
                case 12: {
                    printf(" %lc %c", 0x2666, "Q");
                    break;
                }
                case 13: {
                    printf(" %lc %c", 0x2666, "K");
                    break;
                }
            }
            break;
        }
        case 40 ... 52: {
            switch(card%13){
                case 11: {
                    printf(" %lc %c", 0x2660, "J");
                    break;
                }
                case 12: {
                    printf(" %lc %c", 0x2660, "Q");
                    break;
                }
                case 13: {
                    printf(" %lc %c", 0x2660, "K");
                    break;
                }
            }
            break;
        }
    }
}