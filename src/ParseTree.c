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

	node_ptr->rule_num = -1;
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
			child = child->sibling;
		}

		if(current->tkn_ptr != NULL){
			Token_destroy(current->tkn_ptr);
		}
		free(current);
	}
	LinkedList_destroy(stack);
}


//////////
// Move //
//////////

ParseTree_Node *ParseTree_Node_move_preorder(ParseTree_Node *node_ptr){
	if(node_ptr->child != NULL){
		// Move to child if it exists
		return node_ptr->child;
	}
	else if(node_ptr->sibling != NULL){
		// Else, move to sibling if it exists
		return node_ptr->sibling;
	}
	else{
		// Else, move to the sibling of the first ancestor who has one
		ParseTree_Node *current = node_ptr;

		while(1){
			if(current->parent == NULL){
				// No such ancestor exists, given node was the rightmost
				return NULL;
			}
			else if(current->parent->sibling == NULL){
				// Immediate parent does not have a sibling, move to next
				// parent
				current = current->parent;
			}
			else{
				// Immediate parent has a sibling
				return current->parent->sibling;
			}
		}
	}
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
