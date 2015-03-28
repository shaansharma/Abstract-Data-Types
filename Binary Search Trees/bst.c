// bst.c

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include "bst.h"
#include <limits.h>

// see bst.h documentation
struct bsttree *create_bst(void) {
	struct bsttree *tree = malloc(sizeof(struct bsttree));
	tree->root = NULL;
	return tree;
}


// destroy_tree(node) destroys node
// effects: node is deallocated along with all nodes linked to it.
// time: O(n) where n is the number of nodes linked to struct bstnode node.

void destroy_tree(struct bstnode *node) {
	if (NULL == node) {return;}
	destroy_tree(node->left);
	destroy_tree(node->right);
	free(node);
}


// see bst.h documentation
void destroy_bst(struct bsttree *t){
   assert(t);
   destroy_tree(t->root);
   free(t);
}


// see bst.h documentation
struct bstnode *make_bstnode(int val, struct bstnode *l, struct bstnode *r) {
	struct bstnode *new = malloc(sizeof(struct bstnode));
	new->item = val;
	new->left = l;
	new->right = r;
	return new;
}



// see bst.h documentation
bool is_bstempty(struct bsttree *t){
	assert(t);
	return (NULL == t->root);
}


// inorder_node(node) prints all nodes of node in order
//  (left, root, right)
// effects: node's item is printed to the screen, 
//          along with all nodes' items linked to it
// time: O(n) where n is the number of printed nodes
void inorder_node(struct bstnode *node) {
	if (NULL == node) {return;}
	inorder_node(node->left);
	printf("  %d", node->item);
	inorder_node(node->right);
}

// see bst.h documentation
void traverse_inorder(struct bsttree *t){
	assert(t);
	inorder_node(t->root);
	printf("\n");
}

// isBSTHelper(n, max, min) checks if the BST is valid
bool isBSTHelper(struct bstnode *n, int max, int min){
	if(n == NULL){
		return 1;
	}else if(n->item < min || n->item > max){
		return 0;
	}else{
		return isBSTHelper(n->left, n->item -1, min) && isBSTHelper(n->right, max, n->item +1);
	}
}

// see bst.h documentation
bool is_bst(struct bsttree *t){
	assert(t);

	return isBSTHelper(t->root,INT_MAX,INT_MIN);
}



//see bst.h documentation
void bst_insert(int val, struct bsttree *t) {

	struct bstnode *prev = NULL;
	struct bstnode *cur = t->root;
	while(cur != NULL){
		if (val == cur->item) return;
		prev = cur;
		if (val < cur->item) cur = cur->left;
		else cur = cur->right;
	}

	struct bstnode *new = make_bstnode(val, NULL, NULL);
	if (prev == NULL){
		t->root = new;
	} else if (val < prev->item){
		prev->left = new;
	} else {
		prev->right = new;
	}
	
}

//see bst.h documentation
bool bst_search(struct bsttree *t, int val){

	struct bstnode *prev = NULL;
	struct bstnode *cur = t->root;
	while(cur != NULL){
		if (val == cur->item) return true;
		prev = cur;
		if (val < cur->item) cur = cur->left;
		else cur = cur->right;
	}

	return false;
	
}

// bstHeightHelper(n) returns the height of the BST
int bstHeightHelper(struct bstnode *n){

	if(n == NULL){
		return 0;
	}
		int leftDepth = bstHeightHelper(n->left);
		int rightDepth = bstHeightHelper(n->right);

		if(leftDepth > rightDepth){
			return leftDepth + 1;
		}else{
			return rightDepth + 1;
		}
}

//see bst.h documentation
int bst_height(struct bsttree *t){
	assert(t);

	if(t->root == NULL){
		return 0;
	}else{
		return bstHeightHelper(t->root);
	}
}

// mirrorHelper(t) changes the tree so the left and right pointers are swapped  
void mirrorHelper(struct bstnode *t){
	if(t == NULL){
		return;
	}else{
		struct bstnode *temp = t->left;
		t->left = t->right;
		t->right = temp;
		mirrorHelper(t->left);
		mirrorHelper(t->right);
	}
}

//see bst.h documentation
void mirror(struct bsttree *t) { 
	
	mirrorHelper(t->root);

} 
 


