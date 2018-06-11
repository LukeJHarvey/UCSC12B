//
//

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"Dictionary.h"

const int tableSize = 101; 

// Hashing method
// rotate_left()
// rotate the bits in an unsigned int
unsigned int rotate_left(unsigned int value, int shift) {
   int sizeInBits = 8*sizeof(unsigned int);
   shift = shift & (sizeInBits - 1);
   if ( shift == 0 )
      return value;
   return (value << shift) | (value >> (sizeInBits - shift));
}

// pre_hash()
// turn a string into an unsigned int
unsigned int pre_hash(char* input) { 
   unsigned int result = 0xBAE86554;
   while (*input) { 
      result ^= *input++;
      result = rotate_left(result, 5);
   }
   return result;
}

// hash()
// turns a string into an int in the range 0 to m-1
int hash(char* key, int m){
   return pre_hash(key)%m;
}

// All the Node and Dictionary Creation necessary
typedef struct NodeObj{
	struct NodeObj* next;
	char* key;
	char* value;
} NodeObj;

typedef NodeObj* Node;

Node newNode(char* k, char* v) {
	Node N = malloc(sizeof(NodeObj));
	assert(N!=NULL);
	N->next = NULL;
	N->key = k;
	N->value = v;
	return(N);
}

void freeNode(Node* pN) {
	if( pN!=NULL && *pN!=NULL) {
		free(*pN);
		*pN = NULL;
	}
}

void freeNodeList(Node* pN) {
	if( pN!=NULL && *pN!=NULL) {
		freeNodeList(&((*pN)->next));
		free(*pN);
		*pN = NULL;
	}
}

typedef struct DictionaryObj{
	Node* arr;
	int size;
} DictionaryObj;

Dictionary newDictionary() {
	Dictionary D = malloc(sizeof(DictionaryObj));
	assert(D!=NULL);
	D->arr = calloc(tableSize, sizeof(Node));
	D->size = 0;
	return(D);
}

void freeDictionary(Dictionary* pD) {
	Dictionary x = *pD;

	for(int i = 0; i < tableSize; i++) {
		freeNodeList(&(x->arr[i]));
	}

	if(x->arr != NULL && *x->arr != NULL) {
		free(x->arr);
		x->arr = NULL;
	}

	if( pD!=NULL && x!=NULL ){
		free(x);
		x = NULL;
	}
}


// Utility Functions

// isEmpty()
// returns 1 (true) if S is empty, 0 (false) otherwise
// pre: none
int isEmpty(Dictionary D) {
	return D->size == 0 ? 1:0;
}

// size()
// returns the number of (key, value) pairs in D
// pre: none
int size(Dictionary D) {
	return D->size;
}

// lookup()
// returns the value v such that (k, v) is in D, or returns NULL if no 
// such value v exists.
// pre: none
char* lookup(Dictionary D, char* k) {
	int h = hash(k, tableSize);
	Node pos = D->arr[h];
	if(pos == NULL) {
		return NULL;
	}
	if(strcmp(pos->key, k) == 0) {
		return pos->value;
	}
	else {
		while(strcmp(pos->key, k) != 0) {
			pos = pos->next;
			if(pos == NULL) {
				return NULL;
			}
		}
		return pos->value;
	}
}

// insert()
// inserts new (key,value) pair into D
// pre: lookup(D, k)==NULL
void insert(Dictionary D, char* k, char* v) {
	if(lookup(D, k) != NULL) {
		return;
	}
	int h = hash(k, tableSize);
	Node pos = D->arr[h];
	Node N = newNode(k, v);

	if(pos == NULL) {
		D->arr[h] = N;
	}
	else {
		
		N->next = pos;
		D->arr[h] = N;
		
		// insert at tail
		/*)
		while(pos->next!=NULL) {
			pos = pos->next;
		}
		pos->next = N;
		*/
	}
	D->size++;
}

// delete()
// deletes pair with the key k
// pre: lookup(D, k)!=NULL
void delete(Dictionary D, char* k) {
	if(lookup(D, k) == NULL) {
		return;
	}
	int h = hash(k, tableSize);
	Node pos = D->arr[h];
	if(strcmp(pos->key, k) == 0) {
		Node temp = pos->next;
		freeNode(&pos);
		D->arr[h] = temp;
	}
	else {
		while(strcmp(pos->next->key, k) != 0) {
			pos = pos->next;
		}
		Node temp = pos->next;
		pos->next = temp->next;
		freeNode(&temp);
	}
	D->size--;
}

// makeEmpty()
// re-sets D to the empty state.
// pre: none
void makeEmpty(Dictionary D) {
	for(int i = 0; i < tableSize; i++) {
		freeNodeList(&(D->arr[i]));
	}
	D->size = 0;
}

// printDictionary()
// pre: none
// prints a text representation of D to the file pointed to by out
void printDictionary(FILE* out, Dictionary D) {
	for(int i = 0; i < tableSize; i++) {
		Node N = D->arr[i];
		while(N != NULL) {
			fprintf(out, "%s %s\n", N->key, N->value);
			N = N->next;
		}
	}
}





