#pragma once

#define MAX_HEIGHT 1000

typedef struct _SkipList Skiplist;
typedef struct _Node Node; 

struct _SkipList {
	Node * head;
	unsigned int max_level;
	int (*compare) (void *, void *);
};
/*
SkipList's definition
*/

struct _Node {
	Node **next;
	unsigned int size; 
	void *item;
};
/*
Node's definition
/*

Function that inserts I in the skiplist list.
Input: list and the element to insert.
Output: \
*/
Skiplist* insertSkipList(Skiplist *list, void *I);

/*
Function that checks if element I is present in the skiplist list.
Input: list and the element to insert.
Output: element sought or failure.
*/
void* searchSkipList(Skiplist *list, void * I);


/*
Function that determines the number of pointers to include in the new node.
Input: \
Output: number of pointers to include in the new node.
*/
int randomLevel();


/*
Function to instantiate a new node.
Input: an element and the number of pointers to the current node.
Output: new node.
*/
Node* createNode(void *I, int randomLevel);


/*
Function that instantiates an empty list.
Input: list 
Output: empty list.
*/
Skiplist* Skiplist_init(Skiplist *list , int (*compare) (void*,void*));

/*
Function to print the level and the element on the same level. 
*/
void Skiplist_dump(Skiplist *list);


/*
Function that frees all memory allocated for the skip_list.
Input: Skip_list 
Output: \
*/
void deleteSkipList(Skiplist *list);


/*
Function that frees the memory allocated for a Node.
Input : Node 
Output : /
*/
void deleteNode(Node *snode);


/*
Function that return true if list is empty.
*/
int Skiplist_is_empty(Skiplist*list);


/*
Function that return the element.
*/
void* SkipList_get_elem(Skiplist* list, unsigned long i);
