#include <stdlib.h>
#include "tree.h"

void addChild(tree* this, tree* child);
//methods can only have 10 arguments
int MAX_CHILDREN = 3;//10;

tree* new_tree(token* root){
  tree* t = (tree*) malloc(sizeof(tree));
  t->root = *root;
  //t->children = (tree**) malloc(sizeof(tree*) * MAX_CHILDREN);
  t->left = NULL;
  t->middle = NULL;
  t->right = NULL;
  return t;
}

//void addChild(tree* this, tree* child){
//}
