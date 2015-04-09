#include "count.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <limits.h>

struct countNode{
	int value;
	int totalCalls;
	struct countNode *left;
	struct countNode *right;
};

struct count {
	struct countNode *root;
	int uniqueIntegers;
	int totalTimesNext;
	int mostFrequentNumberCalls;
	int mostFrequentNumber;
};

// Count create_Count(void){
// 	Count newCount = malloc(sizeof(struct count));
// 	newCount->value = 0;
// 	newCount->totalCalls = 0;
// 	newCount->left = NULL;
// 	newCount->right = NULL;
// 	return newCount;
// }

Count create_Count(void){
	Count newCount = malloc(sizeof(struct count));
	newCount->root = NULL;
	newCount->uniqueIntegers = 0;
	newCount->totalTimesNext = 0;
	newCount->mostFrequentNumberCalls = 0;
	newCount->mostFrequentNumber = INT_MIN;
	return newCount;
}

void destroyCountHelper(struct countNode *c){
	if (c != NULL){
		destroyCountHelper(c->left);
		destroyCountHelper(c->right);
		free(c);
	}
}

void destroy_Count(Count c){
	destroyCountHelper(c->root);
	free(c);
}

void next(Count c, int i){
	c->totalTimesNext++;
	struct countNode *prev = NULL;
	struct countNode *cur = c->root;
	while(cur != NULL){
		if (i == cur->value){
			cur->totalCalls++;
			if(cur->totalCalls > c->mostFrequentNumberCalls){
				c->mostFrequentNumber = cur->value;
				c->mostFrequentNumberCalls = cur->totalCalls;
			}
			return;
		}
		prev = cur;
		if (i < cur->value) cur = cur->left;
		else cur = cur->right;
	}

	struct countNode *newNode = malloc(sizeof(struct countNode));
	newNode->value = i;
	newNode->totalCalls = 1;
	newNode->left = NULL;
	newNode->right = NULL;
	if(newNode->totalCalls > c->mostFrequentNumberCalls){
		c->mostFrequentNumber = newNode->value;
		c->mostFrequentNumberCalls = newNode->totalCalls;
	}
	if (prev == NULL){
		c->root = newNode;
	} else if (i < prev->value){
		prev->left = newNode;
	} else {
		prev->right = newNode;
	}	
	c->uniqueIntegers++;
}

int total(Count c){
	return c->totalTimesNext;
}

int unique(Count c){
	return c->uniqueIntegers;
}

int count(Count c, int i){
	struct countNode *prev = NULL;
	struct countNode *cur = c->root;
	while(cur != NULL){
		if (i == cur->value){
			return cur->totalCalls;
		}
		prev = cur;
		if (i < cur->value) cur = cur->left;
		else cur = cur->right;
	}
	return 0;
}

int mostfreq(Count c){
	assert(total(c) > 0);
	return c->mostFrequentNumber;
}

void statsHelper(struct countNode *c) {
	if (c == NULL) {return;}
	statsHelper(c->left);
	if(c->totalCalls > 0)
		printf("%d: %d\n", c->value, c->totalCalls);
	statsHelper(c->right);
}

void stats(Count c){
	statsHelper(c->root);
}