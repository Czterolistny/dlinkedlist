#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define BT_TYPE int
#define UNUSED(x) (void)(x)

#define USE_RECURSION 0

#if (USE_RECURSION == 1)
	#define USE_INSERT_RECURSION 0
	#define USE_TRAVERSE_RECURSION 0
	#define USE_DEALLOC_RECURSION 0
#endif

void print_int(int x) { printf("%d\n", x); }
void print_float(float x) { printf("%f\n", x); }
void print_char(char x) { printf("%c\n", x); }
void print_string(char *x) {printf("%s\n", x); }

#define printNODE(X) _Generic((X), \
        int: print_int, \
        float: print_float, \
        char: print_char, \
		char*: print_string)(X)

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
BT_ARGS_t btArgs;

inline BT_TYPE getLeftNodeVal(node_t *node);
inline BT_TYPE getRightNodeVal(node_t *node);
inline static bool isNodeRightLeaf(node_t *node);
inline static bool isNodeLeftLeaf(node_t *node);
inline static int deallocNode(node_t *node);
inline static int printNode(node_t *node);
inline static int compareNodeVal(node_t *node);

int traverseInOrder(node_t *node, BT_ARGS_t *btArgs);
int traverseBreadthFirst(node_t *node, BT_ARGS_t *btArgs);
int traverseDealloc(node_t *node, BT_ARGS_t *btArgs);
node_t *getMostRightNode(node_t *node, int *right_wide);
node_t *getMostLeftNode(node_t *node, int *left_wide);

BT_TYPE getLeftNodeVal(node_t *node)
{
	return node->left->val;
}

BT_TYPE getRightNodeVal(node_t *node)
{
	return node->right->val;
}

static bool isNodeRightLeaf(node_t *node)
{
	if( NULL == node->parent_node )
	{
		return false;
	}
	return (node == node->parent_node->right);
}

static bool isNodeLeftLeaf(node_t *node)
{
	if( NULL == node->parent_node )
	{
		return false;
	}
	return (node == node->parent_node->left);
}

static int deallocNode(node_t *node)
{
	free(node);
}

static int printNode(node_t *node)
{
	printNODE(node->val);
}

static int compareNodeVal(node_t *node)
{
	BT_TYPE val = *(BT_TYPE*) (btArgs.param);
	printf("%d %d\n", node->val, val);
	if(node->val == val)
	{
		(*(int*) (btArgs.returns))++;
	}
}

int printBT(node_t *root_node)
{
	btArgs.action = (void*) &printNode;
	return traverseInOrder(root_node, &btArgs);
}

int printBT_BFS(node_t *root_node)
{
	btArgs.action = (void*) &printNode;
	return traverseBreadthFirst(root_node, &btArgs);
}

int deInitBT(node_t *root_node)
{
	btArgs.action = (void*) &deallocNode;
	return traverseDealloc(root_node, &btArgs);
}

int getMaxDepth(node_t *root_node)
{
}

int getLeftWide(node_t *root_node)
{
	int wide = 0;
	getMostLeftNode(root_node, &wide);
	return wide;
}

int getRightWide(node_t *root_node)
{
	int wide = 0;
	getMostRightNode(root_node, &wide);
	return wide;
}

bool searchBT(node_t *node, BT_TYPE valToSearch)
{
	if( valToSearch > node->val )
	{
		if( NULL == node->right )
		{
			return false;
		}
		node = node->right;
	}else
	if( valToSearch < node->val )
	{
		if( NULL == node->left )
		{
			return false;
		}
		node = node->left;
	}else
	{
		return true;
	}
	searchBT(node, valToSearch);
}

bool isValueExistInBT(node_t *root_node, BT_TYPE val)
{
	static int ret = 0;
	btArgs = (BT_ARGS_t) {.param = (void*) &val, .action = (void*) &compareNodeVal, .returns = (void*) &ret};
	traverseInOrder(root_node, &btArgs);
	return ( *((int*) btArgs.returns) > 0);
}

node_t *goMostDownLeft(node_t *node)
{
	for(; (NULL != node->left) || (NULL != node->right) ;)
	{
		if( NULL != node->left )
		{
			node = node->left;
		}else
		{
			node = node->right;
		}
	}
	return node;
}

node_t *goMostDownRight(node_t *node)
{
	for(; (NULL != node->left) || (NULL != node->right) ;)
	{
		if( NULL != node->right )
		{
			node = node->right;
		}else
		{
			node = node->left;
		}
	}
	return node;
}

static bool isLeaflessNode(node_t *node)
{
	return (NULL == node->right) && (NULL == node->left);
}

node_t *getMostLeftNode(node_t *node, int *left_wide)
{
	for(; NULL != node->left ;)
	{
		node = node->left;
		if( NULL != left_wide )
		{
			(*left_wide)++;
		}
	}
	return node;
}

node_t *getMostRightNode(node_t *node, int *right_wide)
{	
	for(; NULL != node->right ;)
	{
		node = node->right;
		if( NULL != right_wide )
		{
			(*right_wide)++;
		}
	}
	return node;
}

int traverseDealloc(node_t *node, BT_ARGS_t *btArgs)
{
	if( (NULL == btArgs) || (NULL == btArgs->action) )
	{
		return -1;
	}
#if !(USE_DEALLOC_RECURSION == 1)
	for(;;)
#endif
	{
		node = goMostDownLeft(node);
		if( (NULL == node->parent_node) && (NULL == node->right) )
		{	
			btArgs->action(node);
			return 0;
		}else
		{
			node = node->parent_node;
			if( NULL != node->left )
			{
				btArgs->action(node->left);
				node->left = NULL;
			}else
			if( NULL != node->right )
			{
				btArgs->action(node->right);
				node->right = NULL;
			}
		}
	}
#if (USE_DEALLOC_RECURSION == 1)
	traverseDealloc(node, btArgs);
#endif
}

int traverseBreadthFirst(node_t *node, BT_ARGS_t *btArgs)
{
	btArgs->action(node);
}

int traverseInOrder(node_t *node, BT_ARGS_t *btArgs)
{
	if( (NULL == btArgs) || (NULL == btArgs->action) )
	{
		return -1;
	}

#if !(USE_TRAVERSE_RECURSION == 1)
	bool isTraverseUp = false;
	bool right_leaf = false;
	
	for(;;)
#else
	static bool isTraverseUp = false;
	static bool right_leaf = false;
#endif
	{
		
		if( false == isTraverseUp )
		{
			node = getMostLeftNode(node, NULL);
		}
		if( true == isLeaflessNode(node) )
		{
			isTraverseUp = true;
		}
		if( (NULL == node->parent_node) && (true == right_leaf) )
		{
	#if (USE_TRAVERSE_RECURSION == 1)
			isTraverseUp = false;
			right_leaf = false;
	#endif
			return 0;
		}
		if( ((false == right_leaf) && (true == isTraverseUp) ) || ((NULL == node->left) && (false == isTraverseUp)) )
		{
			btArgs->action(node);
		}
		
		if( (false == isTraverseUp) && (NULL != node->right) )
		{
			node = node->right;
		}
		if( (isTraverseUp) && !right_leaf && (NULL != node->right) )
		{
			node = node->right;
			isTraverseUp = false;
		}
		
		if(NULL == node->parent_node)
		{
			puts("root");
			if( NULL == node->right )
			{
				return 0;
			}
			node = node->right;
			isTraverseUp = false;
		}
		if(true == isTraverseUp)
		{	
			right_leaf = isNodeRightLeaf(node);
			node = node->parent_node;
		}
	}
#if (USE_TRAVERSE_RECURSION == 1)
	traverseInOrder(node, btArgs);
#endif
}

node_t * getNodeToInsert(node_t *node, BT_TYPE val)
{
#if !(USE_INSERT_RECURSION == 1)
	for(;;)
#endif
	{
		if( ((NULL == node->left) && (NULL == node->right)) || ((NULL == node->left) && (val < node->val))\
		   		|| ((NULL == node->right) && (val >= node->val)) )
		{
			return node;
		}
		
		if( NULL == node->left )
		{
			node = node->right;
		}else
		if( NULL == node->right )
		{
			node = node->left;
		}else
		{
			if( val >= node->val )
			{
				node = node->right;
			}else
			{
				node = node->left;
			}
		}
	}
#if (USE_INSERT_RECURSION == 1)	
	getNodeToInsert(node, val);
#endif
	
}

int insert(node_t *bt, BT_TYPE val)
{
	static bool inited = false;
	if( NULL == bt )
	{
		return -1;
	}
	if( (NULL == bt->left) && (NULL == bt->right) && (false == inited) )
	{
		bt->val = val;
		inited = true;
		return 0;
	}
	bt = getNodeToInsert(bt, val);
	node_t *new_node = (node_t*) calloc(1, sizeof(node_t));
	new_node->val = val;
	new_node->parent_node = bt;
	
	if( val >= bt->val )
	{
		bt->right = new_node;
	}else
	{
		bt->left = new_node;
	}
	
	return 0;
}

int main(int argc, int **argv)
{
	
	node_t *bt = (node_t*) calloc(1, sizeof(node_t));

	insert(bt, 10);
	insert(bt, 11);
	insert(bt, -1);
	insert(bt, -5);
	insert(bt, 0);
	insert(bt, 1);
	insert(bt, 2);
	insert(bt, 5);
	insert(bt, 4);
	insert(bt, 3);
	insert(bt, -2);
	insert(bt, 16);
	insert(bt, 15);
	insert(bt, 14);
	insert(bt, 13);
	insert(bt, 17);

	printBT(bt);
	//printBT_BFS(bt);
	//printf("r wide: %d\n", getRightWide(bt));
	//printf("l wide: %d\n", getLeftWide(bt));
	deInitBT(bt);
	
return 0;
}
