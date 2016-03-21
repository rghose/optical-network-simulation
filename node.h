#define __NODE_H

#define MAX_CHILD_NODES 10

typedef struct linked_node {
	int node_value;
	struct linked_node *children[MAX_CHILD_NODES];
} node;

node * allocate_new_node(int);

/*
 * This takes some data and initializes the new data
 * with that value.
 * Then returns the child node reference back to the
 * caller function
 */
node * add_child_node(node *, int);
