//list.c

#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>


// see list.h for documentation
struct llist *create_list(void) {
	struct llist *lst = malloc(sizeof(struct llist));
	lst->first = NULL;
	lst->last = NULL;
	lst->len=0;
 	return lst;
}

// see list.h for documentation
void destroy_list(struct llist *lst) {
	assert(lst);
	struct llnode *current = lst->first; 
	struct llnode *next;
	while (current != NULL) {
		next = current->next; // note the next pointer
		free(current); // delete the node
		current = next; // advance to the next node
	}
	free(lst); 
}


// see list.h for documentation
int list_length(struct llist *lst) {
  	assert(lst);
	return lst->len;
}




// see list.h for documentation
void print_list(struct llist *lst) {
  	assert(lst);
	struct llnode *current;
	for (current = lst->first; current != NULL; current = current->next)
		printf("  %d", current->item);
	printf("\n");
}

// see list.h for documentation
void add_first(int n, struct llist *lst) {
	assert(lst);

	struct llnode *new = malloc(sizeof(struct llnode));
	new->item = n;
	new->next = lst->first;
	if((lst->len) == 0){
		lst->first = new;
		lst->last = new;
	}else{
		new->next = lst->first;
		lst->first = new;
	}
	(lst->len)++;
}

// see list.h for documentation
void add_last(int n, struct llist *lst) {
	assert(lst);

	struct llnode *new = malloc(sizeof(struct llnode));
	new->item = n;
	new->next = NULL;
	if((lst->len) == 0){
		lst->first = new;
		lst->last = new;
	}else{
		lst->last->next = new;
		lst->last = new;
	}
	(lst->len)++;
}

// see list.h for documentation
int delete_first(struct llist *lst) {
	assert(list_length(lst) > 0);

	struct llnode *front = lst->first;
	int firstValue = front->item;
	lst->first = lst->first->next;
	free(front);
	(lst->len)--;

	return firstValue;
}

// see list.h for documentation
int get_ith(struct llist *lst, int index) {
	assert((0 <= index) && (index <= (lst->len - 1)));

	int returnItem = 0;

	struct llnode *cur = lst->first;
	struct llnode *prev = NULL;
	for(int i = 0; i <= index; i++){
		if(i == index){
			returnItem = cur->item;
		}else{
			prev = cur;
			cur = cur->next;
		}
	}

	return returnItem;	
}

void insert_ith(struct llist *lst, int index, int data) {
	assert((0 <= index) && (index <= (lst->len)));

	struct llnode *cur = lst->first;
	struct llnode *prev = NULL;
	int i = 0;

	while((cur != NULL) && (index > i)){
		prev = cur;
		cur = cur->next;
		i++;
	}

	struct llnode *new = malloc(sizeof(struct llnode));
	new->item = data;
	new->next = cur;

	if(prev == NULL){
		lst->first = new;
	}else{
		prev->next = new;
	}
	if(cur == NULL){
		lst->last = new;
	}

	(lst->len)++;
}

// see list.h for documentation
void lst_append(struct llist *lst1, struct llist *lst2) {
	assert(lst1);
	assert(lst2);

	lst1->last->next = lst2->first;
	lst1->len += lst2->len;	
	lst2->first = NULL;
	lst2->last = NULL;
	lst2->len = 0;
}

// see list.h for documentation
bool eq_list(struct llist *lst1, struct llist *lst2) {
	assert(lst1);
	assert(lst2);

	if(lst1->len != lst2->len){
		return false;
	}else{
		struct llnode *cur1 = lst1->first;
		struct llnode *prev1 = NULL;
		struct llnode *cur2 = lst2->first;
		struct llnode *prev2 = NULL;

		while((cur1 != NULL) || (cur2 != NULL)){
			if((cur1->item) != (cur2->item)){
				return false;
			}else{
				prev1 = cur1;
				prev2 = cur2;
				cur1 = cur1->next;
				cur2 = cur2->next;
			}
		}
		return true;
	}
}


// see list.h for documentation
int maxminlist(struct llist *lst, int *max, int *min){
	if((lst->first) == NULL){
		return 0;
	}else{
		struct llnode *cur = lst->first;
		struct llnode *prev = NULL;
		*max = cur->item;
		*min = cur->item;
		prev = cur;
		cur = cur->next;
		while(cur != NULL){
			if((cur->item) < *min){
				*min = cur->item;
			}
			if((cur->item) > *max){
				*max = cur->item;
			}
			prev = cur;
			cur = cur->next;
		}
		return 1;
	}
}


// see list.h for documentation
void list_map( struct llist *lst, int (*function_ptr)( int) ) {
	assert(lst);

	struct llnode *cur = lst->first;
	struct llnode *prev = NULL;
	while(cur != NULL){
		cur->item = function_ptr(cur->item);
		prev = cur;
		cur = cur->next;
	}
}