#include "tree2list.h"
#include <stdlib.h>

struct node *tree2listHelper(struct node *root){
	if(root == NULL){
		return root;
	}
	if(root->left != NULL){
		struct node *left = tree2listHelper(root->left);

		while(left->right != NULL){
			left = left->right;
		}

		left->right = root;
		root->left = left;
	}
	if(root->right != NULL){
		struct node *right = tree2listHelper(root->right);

		while(right->left != NULL){
			right = right->left;
		}

		right->left = root;
		root->right = right;
	}

	return root;
}

struct node *tree2list(struct node *root) {
	if(root == NULL){
		return NULL;
	}else{
		root = tree2listHelper(root);

		while(root->left != NULL){
			root = root->left;
		}

		return root;
	}
}