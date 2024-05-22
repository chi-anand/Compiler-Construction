// Group No. : 13
// Adarsh Goel 2020B3A70821P
// Chinmay Anand 2020B3A70800P
// Arjoo Kumari 2020B3A70770P
// Mehak Agarwal 2020B3A70868P
// Jay Prakash Mundhra 2020B3A70799P
#ifndef HASHMAP_H
#define HASHMAP_H

// Linked List hashNode
struct hashNode 
{
	char* key;
	int value;
	struct hashNode* next;
};
typedef struct hashNode * HASHNODE;

struct hashMap 
{

	// Current number of elements in hashMap
	// and capacity of hashMap
	int numOfElements, capacity;

	// hold base address array of linked list
	HASHNODE* arr;
};

typedef struct hashMap* HASHMAP;
// define the functions


void initializeHashMap(HASHMAP mp);
int hashFunction(HASHMAP mp, char* key);
void insert(HASHMAP mp, char* key, int value);
void deleteMap(HASHMAP mp);
int search(HASHMAP mp, char* key);
#endif