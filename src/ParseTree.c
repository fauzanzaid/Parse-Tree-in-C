#include <stdlib.h>


#include "ParseTree.h"
#include "Token.h"


//////////////////////////////////
// Constructors and Destructors //
//////////////////////////////////

ParseTree *ParseTree_new(int symbol, Token *tkn_ptr){
	ParseTree_Node_new(symbol, tkn_ptr);
}

void ParseTree_destroy(ParseTree *tree_ptr){
	ParseTree_Node_destroy(tree_ptr);
}

ParseTree_Node *ParseTree_Node_new(int symbol, Token *tkn_ptr){

}

void ParseTree_Node_destroy(ParseTree_Node *node_ptr){

}


//////////
// Move //
//////////

void ParseTree_Node_move_inorder(ParseTree_Node *node_ptr){

}


//////////////////////
// Modify structure //
//////////////////////

ParseTree_Node *ParseTree_Node_add_child_left_end(ParseTree_Node *node_ptr, int symbol, Token *tkn_ptr){

}
