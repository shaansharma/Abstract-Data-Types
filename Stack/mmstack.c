#include "mmstack.h"
#include <stdlib.h>
#include <assert.h>
#include <limits.h>

struct llnode {
	int item;
	struct llnode *next;
	int min;
	int max;
};

struct mmstack{
	struct llnode *topnode;
	int size;
};

MMStack create_MMStack(void){
	MMStack new = malloc(sizeof(struct mmstack));
	new->topnode = NULL;
	new->size = 0;
	return new;
}

void destroy_MMStack(MMStack mms){
	while (mms->topnode != NULL){
		mms_pop(mms);
	}
	free(mms);
}

int mms_length(MMStack mms){
	return mms->size;
}

void mms_push(MMStack mms, int i){
	struct llnode *new = malloc(sizeof(struct llnode));
	new->item = i;
	new->next = mms->topnode;
	mms->topnode = new;
	mms->size++;
	if(new->next != NULL){
		if(i < new->next->min){
			new->min = i;
		}else{
			new->min = new->next->min;
		}
		if(i > new->next->max){
			new->max = i;
		}else{
			new->max = new->next->max;
		}
	}else{
		new->min = i;
		new->max = i;
	}
}

int mms_pop(MMStack mms){
	assert(mms->size > 0);
	int returnValue = mms->topnode->item;
	struct llnode *temp = mms->topnode;
	mms->topnode = mms->topnode->next;
	mms->size--;
	temp->next = NULL;
	free(temp);
	return returnValue;
}

int mms_min(MMStack mms){
	return mms->topnode->min;
}

int mms_max(MMStack mms){
	assert(mms->size > 0);
	return mms->topnode->max;
}