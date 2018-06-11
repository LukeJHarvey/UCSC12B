//-----------------------------------------------------------------------------
//   IntegerStack.c
//   Implementation file for IntegerStack ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"Block.h"

typedef struct BlockObj{
	char* data;
	long previousHash;
	int id;
} BlockObj;

// Block
typedef BlockObj* Block;

// newBlock()
// constructor of the Block type
Block newBlock(char* data, int id, long h) {
	Block B = malloc(sizeof(BlockObj));
	assert(B!=NULL);
	B->data = data;
	B->previousHash = h;
	B->id = id;
	return(B);
}

// freeBlock()
// destructor for the Block type
void freeBlock(Block* pB){
	if( pB!=NULL && *pB!=NULL ){
		free(*pB);
		*pB = NULL;
	}
}

char* data(Block B) {
	return(B->data);
}
long previousHash(Block B) {
	return(B->previousHash);
}
long hash(Block B) {
	long num = 0;
	for(int i = 0; i < strlen(B->data); i++) {
		num = num +B->data[i];
	}
	num = num + B->previousHash + B->id;
	return(num);
}

// print the block id and data
void printBlock(FILE* out, Block B) {
	if( B==NULL ){
		fprintf(stderr, 
			"Block Error: calling printBlock() on NULL Block reference\n");
		exit(EXIT_FAILURE);
	}
	fprintf(out, "%d:%s:%ld:%ld\n", B->id, B->data, hash(B), previousHash(B));
}



