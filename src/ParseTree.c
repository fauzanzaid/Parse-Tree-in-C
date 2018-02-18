#include <stdlib.h>


#include "ParseTree.h"
#include "Token.h"
#include "LinkedList.h"


//////////////////////////////////
// Constructors and Destructors //
//////////////////////////////////

ParseTree *ParseTree_new(int symbol, Token *tkn_ptr){
	return ParseTree_Node_new(symbol, tkn_ptr);
}

void ParseTree_destroy(ParseTree *tree_ptr){
	ParseTree_Node_destroy(tree_ptr);
}

ParseTree_Node *ParseTree_Node_new(int symbol, Token *tkn_ptr){
	ParseTree_Node *node_ptr = malloc( sizeof(ParseTree_Node) );

	node_ptr->parent = NULL;
	node_ptr->sibling = NULL;
	node_ptr->child = NULL;

	node_ptr->symbol = symbol;
	node_ptr->tkn_ptr = tkn_ptr;

	return node_ptr;
}

void ParseTree_Node_destroy(ParseTree_Node *node_ptr){
	LinkedList *stack =  LinkedList_new();

	LinkedList_push(stack, node_ptr);

	while( LinkedList_peek(stack) != NULL ){
		ParseTree_Node *current = LinkedList_pop(stack);

		// Push all children on to stack
		ParseTree_Node *child = current->child;
		while(child){
			LinkedList_push(stack, child);
		}

		Token_destroy(current->tkn_ptr);
		free(current);
	}

	LinkedList_destroy(stack);
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
	ParseTree_Node *new_node_ptr = ParseTree_Node_new(symbol, tkn_ptr);

	new_node_ptr->parent = node_ptr;
	new_node_ptr->sibling = node_ptr->child;
	node_ptr->child = new_node_ptr;

	return new_node_ptr;
}
