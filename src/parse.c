#include "parse.h"
#include <stdlib.h>
#include <string.h>

token* getToken(char* line);
void advanceCursor(char** pLine, int amount);

int TOKEN_MAX_SIZE = 20;

token* getNextToken(char** pLine){
  //skip white space
  while(**pLine == ' '){
    (*pLine)++;
  }

  token* t = getToken(*pLine);
  advanceCursor(pLine, t->str->length);
  return t;
}

token* getToken(char* line){
  char* endChars; //inclusive
  token_type type;

  if(*line == '"'){
    type = STRING;
    endChars = "\"\0";
    line++; //skip over first "
  }else{
    type = FUNCTION;
    endChars = " ;\0";
  }

  char* str = (char*) malloc(sizeof(char) * TOKEN_MAX_SIZE);
  char* p = str;

  while(!strchr(endChars, *line)){
    *p = *line;
    p++;
    line++;
  }
  *p = '\0';
  cstring* cstr = into_cstring(str);

  //pointer arithmetic. yes im that kind of programmer
  if(p - str <= 0){
    return NULL;
  }

  return new_token(*cstr, type);
}

void advanceCursor(char** pLine, int amount){
  for(; amount > 0; amount--){
    (*pLine)++;
  }
}
