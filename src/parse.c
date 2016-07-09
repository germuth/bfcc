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
  if(**pLine == '\n'){
    return NULL;
  }

  token* t = getToken(*pLine);
  int skips = t->str.length;
  if(t->type == STRING){
    skips += 2; //skip opening and closing "
  }
  advanceCursor(pLine, skips);
  return t;
}

token* getToken(char* line){
  char* endChars; //inclusive
  token_type type;

  //trying to avoid adding semantic meaning, that comes later
  if(strchr("(){}[]+-*/=;", *line)){
    char* str = (char*) malloc(sizeof(char));
    *str = *line;
    line++;
    return new_token(*into_cstring(str), OTHER);
  }else if(*line == '"'){
    type = STRING;
    endChars = "\"";
    line++; //skip over first "
  }else{
    type = OTHER;
    endChars = " (){}[]+-*/=;\n";
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

  return new_token(*cstr, type);
}

void advanceCursor(char** pLine, int amount){
  for(; amount > 0; amount--){
    (*pLine)++;
  }
}
