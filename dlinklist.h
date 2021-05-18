/** 
*	@file dlinklist.h
*	@brief Double linked list header file
*
*	@author xxx
*
*	@date 00/00/00
*/
#ifndef _DLINKLIST_H_
#define _DLINKLIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * Node struct typedef
 */
typedef struct Node Node;

/**
 * Node structure
 */
struct Node{
	/*@{*/
	Node *prev; /**< Pointer to previous node */
	Node *next; /**< Pointer to next node */
	int val;	/**< Node value */
	/*@}*/
};

/**
 * Double linked list structure
 */
typedef struct {
	/*@{*/
	Node *node; /**< Node pointer */
	/*@}*/
	/**
	 * @name Dlinklist parameters
	 */
	/*@{*/
	int size;	/**< Linked list lenght */
	int cur_pos;/**< Current set node */
	/*@}*/
}DoubleLinkList;

void init(DoubleLinkList *dl);
int set_pos(DoubleLinkList *dl, int idx);
int get_cur_pos(DoubleLinkList *dl);
void free_all(DoubleLinkList *dl);
int insert_item(DoubleLinkList *dl, int idx, int val);
int remove_item(DoubleLinkList *dl, int idx);
int remove_end(DoubleLinkList *dl);
int remove_beg(DoubleLinkList *dl);
int set_pos_end(DoubleLinkList *dl);
int set_pos_beg(DoubleLinkList *dl);
int push_end(DoubleLinkList *dl, int val);
int push_beg(DoubleLinkList *dl, int val);
int get_size(DoubleLinkList *dl);
bool get_next_val(DoubleLinkList *dl, int *ret_val);
bool get_prev_val(DoubleLinkList *dl, int *ret_val);
int get_cur_val(DoubleLinkList *dl);
int find_item(DoubleLinkList *dl, int start_idx, int val);
int reverse(DoubleLinkList *dl);
void print_all(DoubleLinkList *dl, void(*print_ptr)(void*));
void print_nodes(DoubleLinkList *dl);

#endif