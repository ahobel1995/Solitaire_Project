#include <stdio.h>

int main(){
  FILE* file;
  char ch;
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

  return 0;
}