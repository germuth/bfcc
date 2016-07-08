#include "parse.h"
#include <stdlib.h>
#include <string.h>

int getTokenPos(char* line);
int find(char* line, char* match);
int contains(char c, char* match);

int isCleanable(char c);

int TOKEN_MAX_SIZE = 20;

//TODO
//was changing bfcc.c to use parse.c and token.c
//can't decide if i can take out code for another method
//because im supposed to change pLine. Thats why i got a
//pointer to pointer
//might make more sense to have this method just find token
//and some other method advance cursor
//but that seems bad at the same time, don't want calling code to be complex
//so i guess i have a wrapper function in here that does both :( I don't know
//man
//also btw when this method is done it will prob replace
//all the old methods so make sure to remove them
token* getToken(char** pLine){
  int numChar = 0;
  char* line = *pLine;
  char* endOfToken; //inclusive
  token_type type;

  if(*line == '"'){
    type = STRING;
    endOfToken = "\"\0";
    line++; //skip over first "
  }else{
    type = FUNCTION;
    endOfToken = " \0";
  }

  char* str = (char*) malloc(sizeof(char) * TOKEN_MAX_SIZE);

  while(strchr(endOfToken, *line);
    *str = *line;
    str++;
    line++;
  }

  if(*pLine <= 0){
    return NULL;
  }

  return my_cstring;
}

int getTokenPos(char* line){
  //string parse until " " 
  if(*line == '"'){
    line++;
    return 1 + find(line, "\"");
  }else{
    return 1 + find(line, " ");
    int count = 0;
    while(1){
      if(*line == ' '){
        return ++count; //want to grab space to be cleaned
      }else if(*line == '\0'){
        return count;
      }
      count++;
      line++;
    }
  }
}

int isCleanable(char c){
  if(c == '(' || c== ')'){
    return 1;
  } else if(c == ';'){
    return 1;
  } else if(c == ' '){
    return 1;
  }
  return 0;
}

void clean(cstring* my_cstring){
  //goes ever entire string
  char* p = my_cstring->i;
  //everything behind q is clean
  char* q = my_cstring->i;

  while(*p != '\0'){
    if( p != q){
      *p = *q;
    }

    if( !isCleanable(*p) ){
      q++;
    }
    p++;
  }
  *q = '\0';
}
