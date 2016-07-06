#include <stdio.h>
#include <stdlib.h>
#include "bfcc.h"
#include "cstring.h"
#include "string.h"

int main(int argc, char **argv){
  if(argc <= 0){
    return -1;
  }
  char* filename = argv[1];

  FILE *pInputFile;
  pInputFile = fopen(filename, "r");
  //fp = fopen("/etc/vim/vimrc", "r");
  if (pInputFile == NULL){
    exit(EXIT_FAILURE);
  }

  FILE *pOutputFile;
  pOutputFile = fopen("output/out.asm", "w");

  cstring* data;
  data = (cstring*) malloc(1000);
  int dataIdx = 0;
  cstring* text;
  text = (cstring*) malloc(1000);
  int textIdx = 0;

  int levelsDeep = 0;

  char line[2560];
  //array of 15 pointers
  //char** tokens = (char**) malloc(15);
  cstring* tokens = (cstring*) malloc(15);
  int currToken = 0;

  //char** functionStack = (char**) malloc(50);
  //char* pNull = "NULL";
  cstring* functionStack = (cstring*) malloc(50);

  functionStack = new_cstring(10);
  functionStack->i = "NULL";
  functionStack++;

  //TODO no point in going line by line anymore, just grab tokens...
  while(fgets(line, sizeof(line), pInputFile)){
    cstring* token = getToken(line);
    while(token != NULL){
      //handle token
      //remove brackets, semicolons, etc
      clean(token);
      tokens[currToken++] = *token;

      token = getToken(line);
    }

    int i;
    //TODO perhaps state machine might be nice?
    for(i = 0; i <= currToken; i++){
      cstring curr = tokens[i];

      //isLiteral (num, string)

      if( curr.i[0]  == '"' ){
        //is string
        char* str = (char*) malloc(100);
        //TODO all strings are named out_string...
        sprintf(str, "out_string:  .asciiz %s", curr.i);
        data[dataIdx++] = *into_cstring(str);
      } else {
        //is function

        //is user function

        //is system function
        if( strcmp(token->i,"printf")) {
        }else{
          text[textIdx++] = *into_cstring("li $v0, 4"); //system call code for printing string
          //TODO we always print out_string...
          text[textIdx++] = *into_cstring("la $a0, out_string"); //system call code for printn string
          text[textIdx++] = *into_cstring("syscall"); //execute prev loaded syscall
        }
      }
    }
    //DATA Section
    fprintf(pOutputFile, "        .data");
    for(i = 0; i <= dataIdx; i++){
      fprintf(pOutputFile, data[i].i);
      fprintf(pOutputFile, "\n");
    }
    fprintf(pOutputFile, "\n");

    //TEXT Section
    fprintf(pOutputFile, "        .text");
    for(i = 0; i <= dataIdx; i++){
      fprintf(pOutputFile, text[i].i);
      fprintf(pOutputFile, "\n");
    }
    fprintf(pOutputFile, "li $v0, 10");//load terminate program
    fprintf(pOutputFile, "syscall");//execute prev loaded program
  }

  fclose(pInputFile);
  exit(EXIT_SUCCESS);
}

//advances down the line and returns the token it passed through
cstring* getToken(char* line){
  int tokenSize = getTokenPos(line);
  if(tokenSize <= 0){
    return NULL;
  }

  //char* token = (char*) malloc(tokenSize);
  cstring* token;
  token->length = tokenSize;
  token->i = (char*) malloc(25);

  //copy token to new string
  int i;
  for(i = 0; i < tokenSize; i++){
    token->i = *line;
    token->i++;
    line++;
  }

  //TODO i should be using new pointers rather than resetting
  //restore token pointer to beginning
  for(i = 0; i < tokenSize; i++){
    token->i--;
  }

  return token;
}

int getTokenPos(char* line){
  int count = 0;
  int space = 0;
  while(!space){
    if(*line == ' '){
      space = 1;
    }else if(*line == '\0'){
      //reached end of string
      space = 1;
    } else {
      count++;
      line++;
    }
  }
  //restore pointer to original starting point
  int i;
  for(i = 0; i < count; i++){
    line--;
  }
  return count;
}
