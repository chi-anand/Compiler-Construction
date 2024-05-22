// Group No. : 13
// Adarsh Goel 2020B3A70821P
// Chinmay Anand 2020B3A70800P
// Arjoo Kumari 2020B3A70770P
// Mehak Agarwal 2020B3A70868P
// Jay Prakash Mundhra 2020B3A70799P
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashMap.h"


// like constructor
void initializeHashMap(HASHMAP mp)
{

	// Default capacity in this case
	mp -> capacity = 100;
	mp -> numOfElements = 0;

	// array of size = 1
	mp  ->  arr = (HASHNODE*)malloc(sizeof(HASHNODE) * mp -> capacity);
	memset(mp  ->  arr, 0, sizeof(HASHNODE) * mp -> capacity);
	return;
}

int hashFunction(HASHMAP mp, char* key)
{
	int bucketIndex;
	int sum = 0, factor = 31;
	int i = 0;
	while(key[i] != '\0')
	{
		sum = (sum  + ((int)key[i] * factor) % mp -> capacity) % mp -> capacity;
		factor = (factor * 31) % __INT16_MAX__;
		++i;
	}

	bucketIndex = sum;
	if(bucketIndex < 0)
		bucketIndex += mp -> capacity;
	return bucketIndex;
}

void insert(HASHMAP mp, char* key, int value)
{

	// Getting bucket index for the given
	// key - value pair
	int bucketIndex = hashFunction(mp, key);
	HASHNODE newNode = (HASHNODE)malloc(sizeof(struct hashNode));

	// Setting value of node
    newNode -> key = key;
	newNode -> value = value;
	newNode -> next = NULL;

	// Bucket index is empty....no collision
	if (mp -> arr[bucketIndex] == NULL) {
		mp -> arr[bucketIndex] = newNode;
	}

	// Collision
	else {

		newNode -> next = mp -> arr[bucketIndex];
		mp -> arr[bucketIndex] = newNode;
	}
	return;
}

void deleteMap(HASHMAP mp)
{
    for(int i = 0; i < mp  ->  capacity; ++i)
    {
        HASHNODE prev = NULL;
        HASHNODE curr = (mp  ->  arr)[i];
        while(curr != NULL)
        {
            prev = curr;
            curr = curr  ->  next;
            free(prev); 
        }
    }
    free(mp  ->  arr);
}

int search(HASHMAP mp, char* key)
{

	// Getting the bucket index
	// for the given key
	int bucketIndex = hashFunction(mp, key);

	// Head of the linked list
	// present at bucket index
	HASHNODE bucketHead = mp -> arr[bucketIndex];
	while (bucketHead != NULL) 
	{

		// Key is found in the hashMap
		if (strcmp(bucketHead -> key, key) == 0) 
			return bucketHead -> value;
		
		bucketHead = bucketHead -> next;
	}

	return -1;
}


