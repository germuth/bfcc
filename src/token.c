#include "token.h"
#include <stdlib.h>
#include <stdio.h>

token* new_token(cstring* str, token_type type){
  token* t = (token*) malloc(sizeof(token));
  t->str = str;
  t->type = type;
  return t;
}

int isLiteral(token* t){
  return
      t->type == STRING ||
      t->type == NUMBER;
}
