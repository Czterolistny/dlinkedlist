/** 
*	@file dlinklist.c
*	@brief Double linked list source file
*
*	@author xxx
*
*	@date 00/00/00
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "dlinklist.h"

/**
 * @brief Initialize double linked list structure
 *	Initialize double linked list parameters
 * @param[in] *dl Double linked list structure pointer
 * @return 
 */
void init(DoubleLinkList *dl)
{
	assert( dl != NULL );
	dl->node= NULL;
	dl->size = 0;
	dl->cur_pos = -1;
	
}

/**
 * @brief Free allocated dlllist
 *	Free allocated memory for all nodes and dl structure
 * @param[in] *dl Double linked list structure pointer
 * @return 
 */
void free_all(DoubleLinkList *dl)
{
	set_pos_end(dl);
	for(int i = 0; i < dl->size - 1; ++i){
		//assert(dl->node->prev == NULL);
		dl->node = dl->node->prev;
		//assert(dl->node->next == NULL);
		free(dl->node->next);
	}
	free(dl->node);
	free(dl);

}

/**
 * @brief Set node index to read and write
 *	Set node selected by idx, if idx > dl size then
 * node is set to last node
 * @param[in] *dl Double linked list structure pointer
 * @param[in] idx Node index
 * @return 0 if success, -1 if fail
 */
int set_pos(DoubleLinkList *dl, int idx)
{
	assert( dl->node != NULL );
	if( (idx >= dl->size) || (idx < 0) )
		return -1;

	int span = idx - dl->cur_pos;
	dl->cur_pos += span;
	if( span != 0 ){
		for(; span < 0 ;){
			dl->node = dl->node->prev;
			span++;
		}
		for(; span > 0 ;){
			dl->node = dl->node->next;
			span--;
		}
	}

	return 0;
}

/**
 * @brief Set node to last element in dllist
 * @param[in,out] *dl Double linked list structure pointer
 * @return 0 if success, -1 if fail
 */
int set_pos_end(DoubleLinkList *dl)
{
	assert( dl->node != NULL );
	if( set_pos(dl, dl->size - 1) == -1)
		return -1;
	return 0;
}

/**
 * @brief Set node to first element in dllist
 * @param[in,out] *dl Double linked list structure pointer
 * @return 0 if success, -1 if fail
 */
int set_pos_beg(DoubleLinkList *dl)
{
	assert( dl->node != NULL );
	if( set_pos(dl, 0) == -1)
		return -1;
	return 0;
}

/**
 * @brief Get current position
 * @param[in] *dl Double linked list structure pointer
 * @return current node if success, -1 if fail
 */
int get_cur_pos(DoubleLinkList *dl)
{
	if( dl->node == NULL )
		return -1;
	return dl->cur_pos;
}

/**
 * @brief Insert item at specified index
 * If index is higher or equal current node position
 * current position is incremented by 1
 * @param[in,out] *dl Double linked list structure pointer
 * @param[in] idx Node index
 * @param[in] val Value to insert
 * @return 0 if success, -1 if fail
 */
int insert_item(DoubleLinkList *dl, int idx, int val)
{
	assert( dl->node != NULL );
	int cur_pos = dl->cur_pos;
	if( set_pos(dl, idx) == -1 )
		return -1;

	if( cur_pos >= idx ){
		cur_pos++;
	}

	Node *cur_node = dl->node;
	Node *new = (Node*) malloc(sizeof(Node));
	if( dl->node->prev == NULL ){
		dl->node->prev = new;
		dl->node->prev->prev = NULL;
		dl->node->prev->next = cur_node;
		dl->node->prev->val = val;
	}else{
		Node *prev = dl->node->prev;
		dl->node->prev = new;
		dl->node->prev->next = cur_node;
		dl->node->prev->prev = prev;
		dl->node->prev->prev->next = new;
		dl->node->prev->val = val;
	}
	dl->cur_pos++;
	dl->size++;
	set_pos(dl, cur_pos); 

	return 0;
}

/**
 * @brief Add item at the end of linked list
 * current position is incremented by 1
 * @param[in,out] *dl Double linked list structure pointer
 * @param[in] val Value to insert
 * @return 0 if success, -1 if fail
 */
int push_end(DoubleLinkList *dl, int val)
{

	if( dl->cur_pos == -1 )
		dl->cur_pos = 0;

	if( dl->node == NULL){
		dl->node = (Node*) malloc(sizeof(Node));
		dl->node->val = val;
		dl->size = 1;
	}else {
		int cur_pos = dl->cur_pos;
		if( set_pos(dl, dl->size - 1) == -1)
			return -1;
		dl->node->next = (Node*) malloc(sizeof(Node));
		dl->node->next->next = NULL;
		dl->node->next->prev = dl->node;
		dl->node->next->val = val;
		set_pos(dl, cur_pos);
		dl->size++;
	}
	
	return 0;
}

/**
 * @brief Add item at the begin of linked list
 * If index is higher or equal current node position
 * current position is incremented by 1
 * @param[in,out] *dl Double linked list structure pointer
 * @param[in] val Value to insert
 * @return 0 if success, -1 if fail
 */
int push_beg(DoubleLinkList *dl, int val)
{

	if( dl->cur_pos == -1 )
		dl->cur_pos = 0;

	if( dl->node == NULL){
		dl->node = (Node*) malloc(sizeof(Node));
		dl->node->val = val;
		dl->size = 1;
	}else {
		int cur_pos = dl->cur_pos;
		set_pos(dl, 0);
		dl->node->prev = (Node*) malloc(sizeof(Node));
		dl->node->prev->prev = NULL;
		dl->node->prev->next = dl->node;
		dl->node->prev->val = val;
		dl->cur_pos += 1;
		dl->size++;
		set_pos(dl, cur_pos + 1);
	}
	
	return 0;
}

/**
 * @brief Remove item at specified index
 * If index is lower or equal current node position
 * current position is decremented by 1
 * @param[in,out] *dl Double linked list structure pointer
 * @param[in] idx Node index
 * @return 0 if success, -1 if fail
 */
int remove_item(DoubleLinkList *dl, int idx)
{	
	assert( dl->node != NULL );
	
	if( dl->size == 1){
		free(dl->node);
		dl->node = NULL;
		dl->cur_pos = -1;
		dl->size = 0;
		return 0;
	}

	int cur_pos = dl->cur_pos;
	if( set_pos(dl, idx) == -1 )
		return -1;	

	if( idx == 0 ) {
		dl->node = dl->node->next;
		free(dl->node->prev);
		dl->node->prev = NULL;	
	}else if( idx == dl->size - 1){
		dl->node = dl->node->prev;
		free(dl->node->next);
		dl->node->next = NULL;
		dl->cur_pos--;
	}else {
		Node *node_remv = dl->node;
		dl->node->next->prev = dl->node->prev;
		dl->node->prev->next = dl->node->next;
		dl->node = dl->node->next;
		free(node_remv);
		node_remv = NULL;
	}
	
	if( idx < cur_pos )
		cur_pos--;
	
	dl->size--;
	set_pos(dl, cur_pos);
	
	return 0;
}

/**
 * @brief Remove last item
 * @param[in,out] *dl Double linked list structure pointer
 * @return 0 if success, -1 if fail
 */
int remove_end(DoubleLinkList *dl)
{
	return remove_item(dl, 0);
}

/**
 * @brief Remove first item
 * @param[in,out] *dl Double linked list structure pointer
 * @return 0 if success, -1 if fail
 */
int remove_beg(DoubleLinkList *dl)
{
	return remove_item(dl, dl->size - 1);
}

/**
 * @brief Linked list size
 * @param[in,out] *dl Double linked list structure pointer
 * @return Linked list size
 */
int get_size(DoubleLinkList *dl)
{
	assert( dl != NULL );
	return dl->size;
}

/**
 * @brief Get value at current node
 * @param[in,out] *dl Double linked list structure pointer
 * @return Value
 */
int get_cur_val(DoubleLinkList *dl)
{
	assert( dl->node != NULL );
	return dl->node->val;
}

/**
 * @brief Get value at next node
 * @param[in,out] *dl Double linked list structure pointer
 * @param[out] *ret_val pointer to next node value
 * return true if next node exist, false otherwise
 */
bool get_next_val(DoubleLinkList *dl, int *ret_val)
{
	assert( dl->node != NULL );
	if(dl->node->next == NULL)
		return false;
	
	dl->node = dl->node->next;
	*ret_val = dl->node->val;
	dl->cur_pos++;
	return true;
}

/**
 * @brief Get value at previous node
 * @param[in,out] *dl Double linked list structure pointer
 * @param[out] *ret_val pointer to previous node value
 * return true if previous node exist, false otherwise
 */
bool get_prev_val(DoubleLinkList *dl, int *ret_val)
{
	assert( dl->node != NULL );
	if(dl->node->prev == NULL)
		return false;
	
	dl->node = dl->node->prev;
	*ret_val = dl->node->val;
	dl->cur_pos--;
	return true;
}

/**
 * @brief Replace node value
 * Replace value at specified index with val
 * @param[in,out] *dl Double linked list structure pointer
 * @param[in] *idx index to replace value
 * @param[in] val new value
 * return 0 if success, -1 otherwise
 */
int replace_item(DoubleLinkList *dl, int idx, int val)
{
	assert( dl->node != NULL );
	int cur_pos = dl->cur_pos;
	if( set_pos(dl, idx) == -1)
		return -1;
	
	dl->node->val = val;
	set_pos(dl, cur_pos);
	return 0;
}

/**
 * @brief Find value
 * Check if value exist in linked list 
 * Searching is performed from start_idx to last element
 * @param[in,out] *dl Double linked list structure pointer
 * @param[in] start_idx begin index for search
 * @param[in] val value to search for
 * return value index if success, -1 othrewise
 */
int find_item(DoubleLinkList *dl, int start_idx, int val)
{
	assert( dl->node != NULL );
	int cur_pos = dl->cur_pos;
	if( set_pos(dl, start_idx) == -1)
		return -1;
	
	int ret_val; 
	int find_idx = -1;
	
	ret_val = get_cur_val(dl);
	do{
		if( ret_val == val ){
			find_idx = get_cur_pos(dl);
			break;
		}
	}while( get_next_val(dl, &ret_val) );
		   
	set_pos(dl, cur_pos);
	return find_idx;
}

/**
 * @brief Reverse Linked list
 * Not implemented
 * return 0 if success, -1 otherwise
 */
int reverse(DoubleLinkList *dl)
{
	assert( dl->node != NULL );
	int cur_pos = dl->cur_pos;
	set_pos(dl, 0);
	
	set_pos(dl, cur_pos);
	return 0;
}

/**
 * @brief Print all node values
 * @param[in,out] *dl Double linked list structure pointer
 * @param[in,out] *print_ptr print function pointer
 * return 
 */
void print_all(DoubleLinkList *dl, void(*print_ptr)(void*))
{
	assert( dl->node != NULL );
	int cur_pos = dl->cur_pos;
	set_pos(dl, 0);

	int val;
	val = get_cur_val(dl);
	print_ptr(&val);
	while( get_next_val(dl, &val) ){
		print_ptr(&val);
	}
	set_pos(dl, cur_pos);
}

/**
 * @brief Print nodes pointers
 * @param[in,out] *dl Double linked list structure pointer
 * return
 */
void print_nodes(DoubleLinkList *dl)
{
	assert( dl->node != NULL );
	int cur_pos = dl->cur_pos;
	set_pos(dl, 0);
	printf("0: %p %p %p\n", (void*) dl->node->prev, (void*) dl->node, \
		   (void*) dl->node->next);
	for(int i = 0; i < dl->size - 1; ++i){
		dl->node = dl->node->next;
		dl->cur_pos++;
		printf("%d: %p %p %p\n", i+1, (void*) dl->node->prev, (void*) dl->node, \
			   (void*) dl->node->next);
	}
	set_pos(dl, cur_pos);
}