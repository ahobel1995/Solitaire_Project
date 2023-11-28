
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

  char decisionArray[6]; //main array that user input is stored to
  int i=0, correct = 0, colSelect, rowSelect, colToPlace; //helpful variables
  
  while (correct == 0) { //main loop for input, loops until a valid input is entered
    for (i=0;i<6;i++){
      decisionArray[i]='\0'; //initilize decision array with NULLs each loop iteration
    }
    printf("Enter your move: ");
    fgets(decisionArray,6,stdin); //user input
    if ((decisionArray[4] != '\0' && decisionArray[4] != '\n')) { //checks for how many actual chars were entered before newline character, so that the while loop only runs when the user has used all the allocated fgets bytes up to the buffer. That way the getchar loop will clean up overflowed chars only when needed. without this if the user enters less than the allocated bytes, they will have to hit enter twice, once to terminate fgets and once to terminate the getchar loop.
      while (getchar() != '\n'); }
    printf("%c | %c | %c | %c\n",decisionArray[0],decisionArray[1],decisionArray[2],decisionArray[3]); //debug
    
    //===========Move Syntax Logic===========//
    if  ((decisionArray[4] == '\n') || (decisionArray[4] =='\0')) { // checks for if the user entered more than 4 actual chars
      
     
     if ((decisionArray[0] >=48) && (decisionArray[0] <= 55)) {
       colSelect = decisionArray[0]-48;
       printf("colSelect = %d\n",colSelect); //debug
       
       if (((decisionArray[3] >=48) && (decisionArray[3] <= 55)) && (decisionArray[0] != 48)) {
         colToPlace = decisionArray[3]-48;
         printf("colToPlace = %d\n",colToPlace); //debug
         if ((decisionArray[1] == 49) && ((decisionArray[2] >=48) && (decisionArray[2] <= 57))) {
           rowSelect = 10 + decisionArray[2]-48;
           printf("rowSelect = %d\n",rowSelect); //debug
           correct = 1;
         }
         else {
           printf("Invalid move syntax 1\n");
         }
       }
       else if ((decisionArray[3] == '\n') && (decisionArray[0] != 48)) {
         if ((decisionArray[2] >=48) && (decisionArray[2] <= 55)) {
           colToPlace = decisionArray[2]-48;
           printf("colToPlace = %d\n",colToPlace); //debug
           if ((decisionArray[1] >=49) && (decisionArray[1] <= 57)) {
             rowSelect = decisionArray[1]-48;
             printf("rowSelect = %d\n",rowSelect); //debug
             correct = 1;
           }
           else {
             printf("Invalid move syntax 2\n");
           }
         }
         else {
           printf("Invalid move syntax 3\n");
         }
       }
       else if ((decisionArray[2] == '\n') && (decisionArray[3] == '\0')) {
         if ((decisionArray[1] >=48) && (decisionArray[1] <= 55)) {
           colToPlace = decisionArray[1]-48;
           printf("colToPlace = %d\n",colToPlace); //debug
           correct = 1;
         }
         else {
           printf("Invalid move syntax 4\n");
         }
       }
       else {
         printf("Invalid move syntax 5\n");
       }
     }
      
     else if (decisionArray[1] == '\n') {
        if ((decisionArray[0] >= 67 ) && (decisionArray[0] <=81)) {
          decisionArray[0] = decisionArray[0] + 32;
        }
        if (decisionArray[0] == 'q') {
          printf("Quit\n");
          correct = 1;
        }
        else if (decisionArray[0] == 'c') {
          printf("Cycle");
          correct = 1;
        }
        else if (decisionArray[0] == 'h') {
          printf("Help\n");
          correct = 1;
        }
        else {
          printf("Invalid move syntax letter\n");
        }
      }
      else if (colSelect != decisionArray[0]-48) {
        printf("Invalid move syntax\n");
      }
      
    }
    else {
      printf("Too many characters\n");
    }
  }
  
  return 0;
}