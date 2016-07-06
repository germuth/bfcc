#ifndef CSTRING_H
#define CSTRING_H

typedef struct {
  char* i;
  int length;
  int pos;
} cstring;

cstring* new_cstring(int length);
cstring* into_cstring(char* str);
void clean(cstring* this);
char last_char(cstring* this);

#endif //CSTRING_H
