#ifndef TREE_H
#define TREE_H

#include "token.h"

typedef struct {
  token root;
  tree* left;
  tree* middle;
  tree* right;
  //lets just hardcode 3 children for now until i figure out arraylist
  //tree** children;//list of pointers to children
} tree;

tree* new_tree(token* root);
//void addChild(tree* this, tree* child);

#endif //TREE_H
