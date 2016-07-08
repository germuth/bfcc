#include "cstring.h"
#include <stdlib.h>
#include <stdio.h>

cstring* new_cstring(int length){
  cstring* my_cstring = (cstring*) malloc(sizeof(cstring));
  my_cstring->i = (char*) malloc(sizeof(char) * length + 1);
  my_cstring->length = length;
  my_cstring->pos = 0;
  return my_cstring;
}

cstring* into_cstring(char* str){
  cstring* my_cstring = (cstring*) malloc(sizeof(cstring));
  my_cstring->i = str;
  int idx = 0;
  while(str[idx++] != '\0');
  my_cstring->length = idx + 1;
  my_cstring->pos = 0;
  return my_cstring;
}

char last_char(cstring* this){
  return this->i[this->length - 1];
}
