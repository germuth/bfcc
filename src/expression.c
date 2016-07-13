#include "expression.h"

int MAX_TOKENS_PER_EXPRESSION = 5;

expresion* new_expression(){
  expression* e = (expression*) malloc(sizeof(expression));
  e->tokens = (token*) malloc(sizeof(token) * MAX_TOKENS_PER_EXPRESSION);
  e->numTokens = 0;
  e->expression_type = UNKNOWN;
}

void add_token(expression* this, token* t){
  if(numTokens + 1 > MAX_TOKENS_PER_EXPRESSION){
    printf("ERROR too many tokens");
    exit(1);
  }

  tokens[numTokens] = t;
  numTokens++;
}
