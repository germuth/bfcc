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

int isCleanable(char c){
  if(c == '(' || c== ')'){
    return 1;
  } else if(c == ';'){
    return 1;
  }
  return 0;
}

void clean(cstring* this){
  //count good characters
  int i;
  int count = 0;
  for(i = 0 ; i < this->length; i++){
    char curr = this->i[i];
    if( !isCleanable(curr) ){
      count++;
    }
  }

  char* clean_str = (char*) malloc(sizeof(char) * count + 1);

  for(i = 0; i < this->length; i++){
    char curr = this->i[i];
    if( !isCleanable(curr)){
      clean_str[0] = curr;
    }
  }
  this->i = &clean_str;
}

char last_char(cstring* this){
  return this->i[this->length - 1];
}
