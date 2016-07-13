#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "token.h"

//l value & r value?
typedef enum {LITERAL, FUNCTION, VARIABLE, DECLARATION, ASSIGNMENT,
  OPERATOR, UNKNOWN} expression_type;
typedef struct {
  token* tokens;
  int numTokens;
  expression_type type;
} expression;

expresion* new_expression();
void set_type(expression* this, expression_type);
void add_token(expression* this, token* t);

#endif //EXPRESSION_H
