#ifndef PARSE_H
#define PARSE_H

#include "cstring.h"
#include "token.h"

token* getToken(char** pLine);
void clean(token* my_cstring);

#endif //PARSE_H
