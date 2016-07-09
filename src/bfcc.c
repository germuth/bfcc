#include <stdio.h>
#include <stdlib.h>
#include "bfcc.h"
#include "cstring.h"
#include "string.h"
#include "parse.h"

int main(int argc, char **argv){
  if(argc <= 0){
    return -1;
  }
  char* filename = argv[1];
  char* ssss;
  ssss = filename;


  FILE *pInputFile;
  pInputFile = fopen(filename, "r");
  //fp = fopen("/etc/vim/vimrc", "r");
  if (pInputFile == NULL){
    exit(EXIT_FAILURE);
  }

  FILE *pOutputFile;
  pOutputFile = fopen("output/out.asm", "w");

  cstring* data;
  data = (cstring*) malloc(sizeof(cstring) * 1000);
  int dataIdx = 0;
  cstring* text;
  text = (cstring*) malloc(sizeof(cstring) * 1000);
  int textIdx = 0;

  int levelsDeep = 0;

  int MAX_LINE_LENGTH = 120;
  char* line = (char*) malloc(sizeof(char) * MAX_LINE_LENGTH);
  //array of 15 pointers
  //char** tokens = (char**) malloc(15);
  token* tokens = (token*) malloc(sizeof(token) * 15);
  int currToken = 0;

  //char** functionStack = (char**) malloc(50);
  //char* pNull = "NULL";
  cstring* functionStack = (cstring*) malloc(sizeof(cstring) * 50);

  functionStack = new_cstring(10);
  functionStack->i = "NULL";
  functionStack++;

  //TODO no point in going line by line anymore, just grab tokens...
  while(fgets(line, MAX_LINE_LENGTH, pInputFile)){
    token* token = getNextToken(&line);
    while(token != NULL){
      //handle token
      //remove brackets, semicolons, etc
      clean(token->str);
      tokens[currToken++] = *token;

      token = getNextToken(&line);
    }

    int i;
    //TODO perhaps state machine might be nice?
    for(i = 0; i <= currToken; i++){
      cstring curr = *(tokens[i].str);

      //isLiteral (num, string)

      if( curr.i[0]  == '"' ){
        //is string
        char* str = (char*) malloc(sizeof(char) * 100);
        //TODO all strings are named out_string...
        sprintf(str, "out_string:  .asciiz %s", curr.i);
        data[dataIdx++] = *into_cstring(str);
      } else {
        //is function

        //is user function

        //is system function
        if( strcmp(curr.i,"printf")) {
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
