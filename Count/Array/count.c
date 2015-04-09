#include "count.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

struct count{
	int numbers[101];
	int totalCalls;
	int totalCallsEach[101];
};

Count create_Count(void){
	Count newCount = malloc(sizeof(struct count));
	newCount->totalCalls = 0;

    for(int i = 0; i < 101; i++){
        newCount->numbers[i] = 0;
    }

    for(int i = 0; i < 101; i++){
        newCount->totalCallsEach[i] = 0;
    }

	return newCount;
}

void destroy_Count(Count c){
	free(c);
}

void next(Count c, int i){
	assert((1 <= i) && (i <= 100));
	c->numbers[i]++;
	c->totalCalls++;
	c->totalCallsEach[i]++;
}

int total(Count c){
	return c->totalCalls;
}

int unique(Count c){
	int uniqueIntegers = 0;
	for(int i = 1; i < 101; i++){
		if(c->numbers[i] > 0){
			uniqueIntegers++;
		}
	}
	return uniqueIntegers;
}

int count(Count c, int i){
	assert((1 <= i) && (i <= 100));
	return c->totalCallsEach[i];
}

int mostfreq(Count c){
	assert(total(c) > 0);
	
	int largestCount = 0;
	int index = 0;
	for(int i = 1; i < 101; i++){
		if(c->numbers[i] > largestCount){
			largestCount = c->numbers[i];
			index = i;
		}
	}

	return index;
}

void stats(Count c){
    int counted = 0;
	for(int i = 1; i < 101; i++){
		counted = count(c,i);
		if(counted > 0){
			printf("%d: %d\n", i, counted);
		}
	}
}