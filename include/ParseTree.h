#ifndef INCLUDE_GUARD_BFA49EDA2F3B4990B79B0B078BF9687E
#define INCLUDE_GUARD_BFA49EDA2F3B4990B79B0B078BF9687E


#include "Token.h"


/////////////////////
// Data Structures //
/////////////////////

typedef struct ParseTree_Node ParseTree_Node;

struct ParseTree_Node{
	ParseTree_Node *parent;
	ParseTree_Node *sibling;
	ParseTree_Node *child;

	int symbol;
	Token *tkn_ptr;
};

typedef ParseTree_Node ParseTree;

//////////////////////////////////
// Constructors and Destructors //
//////////////////////////////////

ParseTree *ParseTree_new(int symbol, Token *tkn_ptr);

void ParseTree_destroy(ParseTree *tree_ptr);

ParseTree_Node *ParseTree_Node_new(int symbol, Token *tkn_ptr);

void ParseTree_Node_destroy(ParseTree_Node *node_ptr);


//////////
// Move //
//////////

ParseTree_Node *ParseTree_Node_move_preorder(ParseTree_Node *node_ptr);


//////////////////////
// Modify structure //
//////////////////////

ParseTree_Node *ParseTree_Node_add_child_left_end(ParseTree_Node *node_ptr, int symbol, Token *tkn_ptr);


#endif
