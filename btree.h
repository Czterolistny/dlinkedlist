#ifndef __BTREE_H__
#define __BTREE_H__

#include <stdbool.h>

#define BT_TYPE int

typedef struct node node_t;
struct node
{
	node_t *parent_node;
	node_t *left;
	node_t *right;
	BT_TYPE val;
};

typedef struct
{
	node_t *root_node;
}bt_t;

typedef struct
{	
	void (*action)(node_t *node);
	void *param;
	void *returns;
}BT_ARGS_t;

int insert(node_t *bt, BT_TYPE val);
int traverseInOrder(node_t *node, BT_ARGS_t *btArgs);
bool searchBT(node_t *node, BT_TYPE valToSearch);
int printBT(node_t *root_node);
int deInitBT(node_t *root_node);

#endif __BTREE_H__