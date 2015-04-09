#include "dictionary.h"
#include <assert.h>
#include <stdlib.h>

struct bstNode{
	void *key;
	void *value;
	struct bstNode *left;
	struct bstNode *right;
};

struct dictionary{
	struct bstNode *root;
	CompareFunction comp_k;
	FreeFunction free_k;
	FreeFunction free_v;
};

Dictionary create_Dictionary(CompareFunction comp_k, FreeFunction free_k, FreeFunction free_v){
	assert(comp_k);
	assert(free_k);
	assert(free_v);

	Dictionary newDict = malloc(sizeof(struct dictionary));
	newDict->root = NULL;
	newDict->comp_k = comp_k;
	newDict->free_k = free_k;
	newDict->free_v = free_v;
	return newDict;
}

void destroyDictHelper(struct bstNode *node, Dictionary dict){
	if(node == NULL) return;
	destroyDictHelper(node->left, dict);
	destroyDictHelper(node->right, dict);
	dict->free_k(node->key);
	dict->free_v(node->value);
	free(node);
}

void destroy_Dictionary(Dictionary dict){
	assert(dict);
	destroyDictHelper(dict->root,dict);
	free(dict);
}

void insert(Dictionary dict, void *k, void *v){
	assert(dict);
	assert(k);
	assert(v);

	struct bstNode *prev = NULL;
	struct bstNode *cur = dict->root;
	while(cur){
		if (cur->key == k){
			free(cur->value);
			cur->value = v;
			return;
		}
		prev = cur;
		if (dict->comp_k(k,cur->key) < 0){
			cur = cur->left;
		}else{
			cur = cur->right;
		}
	}

	struct bstNode *new = malloc(sizeof(struct bstNode));
	new->key = k;
	new->value = v;
	new->left = NULL;
	new->right = NULL;
	if (prev == NULL){
		dict->root = new;
	} else if (dict->comp_k(k,prev->key) < 0) {
		prev->left = new;
	} else {
		prev->right = new;
	}
}

void *lookup(Dictionary dict, void *k){
	assert(dict);
	assert(k);

	struct bstNode *t = dict->root;
	while(t){
		int result = dict->comp_k(k, t->key);
		if(result < 0){
			t = t->left;
		}else if(result > 0){
			t = t->right;
		}else{
			return t->value;
		}
	}
	return NULL;
}