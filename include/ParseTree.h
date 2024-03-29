#ifndef INCLUDE_GUARD_BFA49EDA2F3B4990B79B0B078BF9687E
#define INCLUDE_GUARD_BFA49EDA2F3B4990B79B0B078BF9687E


#include "Token.h"


/////////////////////
// Data Structures //
/////////////////////

/**
 * User defined data type to hold hold additional information for semantic
 * analysis
 */
typedef struct ParseTree_Node_Attr ParseTree_Node_Attr;

typedef struct ParseTree_Node ParseTree_Node;

struct ParseTree_Node{
	ParseTree_Node *parent;
	ParseTree_Node *sibling;
	ParseTree_Node *child;

	int rule_num;
	int symbol_index;
	int symbol;
	Token *tkn_ptr;
	ParseTree_Node_Attr* atr_ptr;
};

typedef ParseTree_Node ParseTree;

//////////////////////////////////
// Constructors and Destructors //
//////////////////////////////////

/**
 * User defined function which allocates and returns a pointer to an instance of
 * user defined @p ParseTree_Node_Attr struct
 * @return Pointer to allocated struct
 */
ParseTree_Node_Attr *ParseTree_Node_Attr_new();

/**
 * User defined function which deallocates the @p ParseTree_Node_Attr struct
 * whose pointer is passed to it
 * @param  atr_ptr Pointer to struct to be destroyed
 */
void ParseTree_Node_Attr_destroy(ParseTree_Node_Attr *atr_ptr);

ParseTree *ParseTree_new(int symbol, Token *tkn_ptr);

void ParseTree_destroy(ParseTree *tree_ptr);

ParseTree_Node *ParseTree_Node_new(int symbol, Token *tkn_ptr);

void ParseTree_Node_destroy(ParseTree_Node *node_ptr);


//////////
// Move //
//////////

ParseTree_Node *ParseTree_Node_move_preorder(ParseTree_Node *node_ptr);

ParseTree_Node *ParseTree_Node_get_child_by_node_index(ParseTree_Node *node_ptr, int node_index);

ParseTree_Node *ParseTree_Node_get_child_by_symbol_index(ParseTree_Node *node_ptr, int symbol_index);


//////////////////////
// Modify structure //
//////////////////////

ParseTree_Node *ParseTree_Node_create_child_left_end(ParseTree_Node *node_ptr, int symbol, Token *tkn_ptr);

void ParseTree_Node_attach_child_left_end(ParseTree_Node *node_ptr, ParseTree_Node *child_ptr);

void ParseTree_Node_attach_sibling(ParseTree_Node *node_ptr, ParseTree_Node *sibling_ptr);

ParseTree_Node *ParseTree_Node_detach_child_by_symbol_index(ParseTree_Node *node_ptr, int symbol_index);

int ParseTree_Node_remove_child_by_symbol_index(ParseTree_Node *node_ptr, int symbol_index);


////////////
// Others //
////////////

int ParseTree_get_node_count(ParseTree *tree_ptr);


#endif
