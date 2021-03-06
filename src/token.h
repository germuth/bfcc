#ifndef TOKEN_H
#define TOKEN_H

#include "cstring.h"

typedef enum {STRING, NUMBER, FUNCTION, OTHER, BRACKET_OPEN, BRACKET_CLOSE,
  BRACE_OPEN, BRACE_CLOSE, OPERATOR, EQUAL, END} token_type;
typedef struct {
  cstring str;
  token_type type;
  int depth;//execution depth within each statement
} token;

token* new_token(cstring str, token_type type);
int isLiteral(token* t);

#endif //TOKEN_H
