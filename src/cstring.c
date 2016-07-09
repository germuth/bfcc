#include "cstring.h"
#include <stdlib.h>
#include <stdio.h>

int isCleanable(char c);

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
  while(str[idx] != '\0'){
    idx++;
  }
  my_cstring->length = idx;
  my_cstring->pos = 0;
  return my_cstring;
}

char last_char(cstring* this){
  return this->i[this->length - 1];
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
  my_cstring->length = (q - my_cstring->i);
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

