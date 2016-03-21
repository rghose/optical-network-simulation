#include <stdio.h>

#ifndef __NODE_H
#include "node.h"
#endif

node *allocate_new_node(int value) {
	node *new_node = (node *)malloc(sizeof(node));
	if (new_node != NULL) {
		new_node->value = value;
	}
	return new_node;
}

node * add_child(node *parent, int value) {
	if(parent == NULL){
		return NULL;
	}
	if(parent->node_number > MAX_CHILD_NODES) {
		return NULL;
	}
	new_child_node = allocate_new_node(value);
	if(new_child_node != NULL) {
		parent->children[parent->node_number] = new_child_node;
		parent->node_number++;
	}
	return new_child_node;
}
