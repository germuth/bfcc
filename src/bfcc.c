#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "bfcc.h"
#include "tree.h"
#include "tree.h"
#include "cstring.h"
#include "string.h"
#include "parse.h"

int MAX_LINE_LENGTH = 120;
int MAX_NUM_LINES=1000;
int MAX_TOKEN_PER_LINE=20;


token* tokens;
int currToken;
token** tokenLines;

int main(int argc, char **argv){
  if(argc <= 0){
    return -1;
  }
  /*
  char* filename = argv[1];
  char* ssss;
  ssss = filename;


  */
  FILE *pInputFile;
  //pInputFile = fopen(filename, "r");
  pInputFile = fopen("input/test.bfc", "r");
  //fp = fopen("/etc/vim/vimrc", "r");
  if (pInputFile == NULL){
    exit(EXIT_FAILURE);
  }

  FILE *pOutputFile;
  pOutputFile = fopen("output/out.asm", "w");

  cstring* data;
  data = (cstring*) malloc(sizeof(cstring) * 1000);
  int dataIdx = 0;
  cstring* text;
  text = (cstring*) malloc(sizeof(cstring) * 1000);
  int textIdx = 0;

  int levelsDeep = 0;

  char* line = (char*) malloc(sizeof(char) * MAX_LINE_LENGTH);
  //array of 15 pointers
  //char** tokens = (char**) malloc(15);
  tokens = (token*) malloc(sizeof(token) * 15);
  currToken = 0;

  //char** functionStack = (char**) malloc(50);
  //char* pNull = "NULL";
  cstring* functionStack = (cstring*) malloc(sizeof(cstring) * 50);

  functionStack = new_cstring(10);
  functionStack->i = "NULL";
  functionStack++;

  //TODO no point in going line by line anymore, just grab tokens...
  while(fgets(line, MAX_LINE_LENGTH, pInputFile)){
    token* token = getNextToken(&line);
    while(token != NULL){
      printf("%s\n", token->str.i);
      //handle token
      //remove brackets, semicolons, etc
      //clean(&(token->str));
      tokens[currToken++] = *token;

      token = getNextToken(&line);
    }
  }

  determineTokenType();

  //should combine tokens into expressions, ex
  //char* my_str; is four tokens but one 'expression'
  //printf("hello world");
  //is two expressions, expression has return value
  //but still need expression tree

  //this is so messy my god help
  tree* expTrees = new (tree*) malloc(sizeof(tree) * MAX_NUM_LINES);
  tree* currTree = expTrees;

  token* currLine = *tokenLines;
  int i;
  for(i = 0; i < currLine; i++){
    if(currTree == NULL){
      expression* root = new_expression();
      root->type = ROOT;
      currTree = new_tree(root);
    }
    token curr = *currLine;
    
    if(curr.type == TYPE){
      //this and next are expression
      //recursive procedure to attach next tokens as expression to current tree
      //this way we can have func( x+y, func2(y*z) )
      //if we need to attach root expression node, perhaps each line should root
      //node
    }
  }

  fclose(pInputFile);
  exit(EXIT_SUCCESS);
}

void determineTokenType(){
  //assign tokens types and place into lines
  tokenLines = (token**) malloc(sizeof(token*) * MAX_NUM_LINES);
  token* currLine = *tokenLines;
  int i;
  int currLinePos = 0;
  for(i = 0; i < currToken; i++){
    token curr = tokens[i];
    //TODO this is kinda messy, should be easier way to get string?
    //but i would have to use a method?
    char c = curr.str.i[0];
    if(currLinePos == 0){
      currLine = (token*) malloc(sizeof(token) * MAX_TOKEN_PER_LINE);
    }
    switch(c){
      case '(':
        curr.type = BRACKET_OPEN;
        break;
      case ')':
        curr.type = BRACKET_CLOSE;
        break;
      case '{':
        curr.type = BRACE_OPEN;
        break;
      case '}':
        curr.type = BRACE_CLOSE;
        break;
      case '"':
        curr.type = STRING;
      case '+':
      case '-':
      case '*':
      case '/':
        curr.type = OPERATOR;
        break;
      case '=':
        curr.type = EQUAL;
        break;
      case ';':
        curr.type = END;
        break;
      default:
        if(isdigit(c)){
          curr.type = NUMBER;
        }else if(isalpha(c)){
          //this is crap, my compiler will have switching on strings!

          //char,int,float,double,one of the declared structs, all the types
          //if(strcmp(curr.i, "char")){
          //curr.type = TYPE;
          //}

          //if(curr.i is keyword){
          //for,if,while,return


          //if(curr.i in environment){
          //  curr.type = VARIABLE/IDENTIFIER


          curr.type = FUNCTION;
        }else{
          printf("Unknown symbol");
        }
        break;
    }

    currLine[currLinePos] = curr;
    currLinePos++;
    if(curr.type == END){
      currLine++;
      currLinePos = 0;
    }

    printf("%s\n", curr.str.i);
  }
}
