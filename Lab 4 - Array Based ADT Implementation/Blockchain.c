//-----------------------------------------------------------------------------
//   IntegerStack.c
//   Implementation file for IntegerStack ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"Blockchain.h"

#define MAX_BLOCK_CHAIN_SIZE 100

// Exported reference type
typedef struct BlockchainObj {
	Block* chain;
	int size;
} BlockchainObj;

typedef struct BlockchainObj* Blockchain;

// constructor for the Blockchain type
Blockchain newBlockchain() {
	Blockchain B = malloc(sizeof(Blockchain));
	B->chain = malloc(MAX_BLOCK_CHAIN_SIZE*sizeof(Block));
	B->size = 0;
	return(B);
}

// destructor for the Blockchain type
void freeBlockchain(Blockchain* pB) {
	Blockchain x = *pB;

	for(int i = 0; i < x->size; i++) {
		freeBlock(&(x->chain[i]));
	}

	if(x->chain != NULL && *x->chain != NULL) {
		free(x->chain);
		x->chain = NULL;
	}

	if( pB!=NULL && x!=NULL ){
		free(x);
		x = NULL;
	}
}

// append a new block to the chain with the data specified in the new block
// return the size of the block chain if successful and 0 otherwise
int append(Blockchain B, char* data) {
	if(B->size >= MAX_BLOCK_CHAIN_SIZE || !valid(B)) {
		return 0;
	}

	long h;
	if(B->size == 0 ) {
		h = 0;
	} else {
		h = hash(B->chain[B->size - 1]);
	}
	Block nBlock = newBlock(data, B->size, h);
	B->chain[B->size] = nBlock;
	B->size++;
	return B->size;
}

// return the number of blocks in this chain
int size(Blockchain B) {
	return B->size;
}

// return the block at index idx in the chain
Block get(Blockchain B, int idx) {
	return B->chain[idx];
}

// check if this is a valid chain by checking the stored previousHash values in each block
// return 1 if valid, 0 otherwise
int valid(Blockchain B) {
	int val = 1;
	long h = 0;
	for(int i = 1; i < B->size; i++) {
		h = hash(get(B, i-1));
		if(h!=previousHash(get(B,i))) {
			val = 0;
		}
	}
	return val;
}

// shorten the chain by revmoing the last block
// do nothing if the chain is already empty
void removeLast(Blockchain B) {
	if(B->size != 0) {
		freeBlock(&(B->chain[B->size-1]));
		B->chain[B->size-1] = NULL;
		B->size--;
	}
}

// print the chain
void printBlockchain(FILE* out, Blockchain B) {
	if( B==NULL ){
		fprintf(stderr, 
			"Blockchain Error: calling printBlock() on NULL Blockchain reference\n");
		exit(EXIT_FAILURE);
	}
	for(int i = 0; i<B->size; i++) {
		printBlock(out,B->chain[i]);
	}
}