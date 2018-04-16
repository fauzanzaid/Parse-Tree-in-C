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
	node_ptr->symbol_index = -1;

	node_ptr->symbol = symbol;
	node_ptr->tkn_ptr = tkn_ptr;
	node_ptr->atr_ptr = ParseTree_Node_Attr_new();

	return node_ptr;
}

void ParseTree_Node_destroy(ParseTree_Node *node_ptr){
	LinkedList *stack =  LinkedList_new();

	LinkedList_push(stack, node_ptr);

	// Push all siblings on to stack
	ParseTree_Node *sibling = node_ptr->sibling;
	while(sibling){
		LinkedList_push(stack, sibling);
		sibling = sibling->sibling;
	}

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

		ParseTree_Node_Attr_destroy(current->atr_ptr);

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

ParseTree_Node *ParseTree_Node_get_child_by_node_index(ParseTree_Node *node_ptr, int node_index){
	ParseTree_Node *child_cur = node_ptr->child;

	while(node_index--){
		child_cur = child_cur->sibling;

		if(child_cur == NULL)
			return NULL;
	}

	return child_cur;
}

ParseTree_Node *ParseTree_Node_get_child_by_symbol_index(ParseTree_Node *node_ptr, int symbol_index){
	ParseTree_Node *child_cur = node_ptr->child;

	while(child_cur != NULL){
		if(child_cur->symbol_index == symbol_index)
			return child_cur;
		child_cur = child_cur->sibling;
	}

	return NULL;
}


//////////////////////
// Modify structure //
//////////////////////

ParseTree_Node *ParseTree_Node_create_child_left_end(ParseTree_Node *node_ptr, int symbol, Token *tkn_ptr){
	ParseTree_Node *new_node_ptr = ParseTree_Node_new(symbol, tkn_ptr);

	new_node_ptr->parent = node_ptr;
	new_node_ptr->sibling = node_ptr->child;
	node_ptr->child = new_node_ptr;

	return new_node_ptr;
}

void ParseTree_Node_attach_child_left_end(ParseTree_Node *node_ptr, ParseTree_Node *child_ptr){
	ParseTree_Node *current = child_ptr;
	while(current->sibling != NULL){
		current->parent = node_ptr;
		current = current->sibling;
	}

	current->parent = node_ptr;
	current->sibling = node_ptr->child;

	node_ptr->child = child_ptr;
}

void ParseTree_Node_attach_sibling(ParseTree_Node *node_ptr, ParseTree_Node *sibling_ptr){
	ParseTree_Node *current = sibling_ptr;
	if(node_ptr->parent != NULL){
		while(current != NULL){
			current->parent = node_ptr->parent;
			current = current->sibling;
		}
	}

	current = sibling_ptr;
	if(node_ptr->sibling != NULL){
		while(current->sibling != NULL){
			current = current->sibling;
		}
		current->sibling = node_ptr->sibling;
	}

	node_ptr->sibling = sibling_ptr;
}

ParseTree_Node *ParseTree_Node_detach_child_by_symbol_index(ParseTree_Node *node_ptr, int symbol_index){
	ParseTree_Node *child_cur = node_ptr->child;
	ParseTree_Node *child_prev = NULL;

	while(child_cur != NULL){
		if(child_cur->symbol_index == symbol_index){
			if(child_prev == NULL)
				node_ptr->child = child_cur->sibling;
			else
				child_prev->sibling = child_cur->sibling;

			child_cur->parent = NULL;
			child_cur->sibling = NULL;

			return child_cur;
		}

		child_prev = child_cur;
		child_cur = child_cur->sibling;
	}

	return NULL;
}

int ParseTree_Node_remove_child_by_symbol_index(ParseTree_Node *node_ptr, int symbol_index){
	ParseTree_Node *child_cur = node_ptr->child;
	ParseTree_Node *child_prev = NULL;

	while(child_cur != NULL){
		if(child_cur->symbol_index == symbol_index){
			if(child_prev == NULL)
				node_ptr->child = child_cur->sibling;
			else
				child_prev->sibling = child_cur->sibling;

			child_cur->parent = NULL;
			child_cur->sibling = NULL;

			ParseTree_Node_destroy(child_cur);
			return 0;
		}

		child_prev = child_cur;
		child_cur = child_cur->sibling;
	}

	return -1;
}


////////////
// Others //
////////////

int ParseTree_get_node_count(ParseTree *tree_ptr){
	int node_count = 0;

	while(1){
		if(tree_ptr == NULL){
			break;
		}

		node_count ++;
		tree_ptr = ParseTree_Node_move_preorder(tree_ptr);
	}

	return node_count;
}
