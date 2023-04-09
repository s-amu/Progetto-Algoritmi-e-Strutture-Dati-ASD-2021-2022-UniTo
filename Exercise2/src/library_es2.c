#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "header_es2.h"

Skiplist *insertSkipList(Skiplist *list, void * I) {
	int level = randomLevel();
	Node *new = createNode(I, level);

	if(new->size > list->max_level) {
		list->max_level = new->size;
	}

	Node* x = list->head ; 
	for(int k = list->max_level-1; k >= 0; k--) {
		if(x->next[k] == NULL || list->compare(I, x->next[k]->item) < 0) {
			if(k < new->size) {
				new->next[k] = x->next[k];
				x->next[k] = new;
			}
		} else {
				x = x->next[k];
				k++;
		}
	}
	return list; 
}

void Skiplist_dump(Skiplist *list) {
	Node *x = list->head;
	while(x && x->next[0] != NULL) {
		fprintf(stderr, "Number of level -> %d Word to insert -> [%s]\n" , x->next[0]->size , (char*)x->next[0]->item);
		x = x->next[0];
	}
}

int randomLevel() {
	int lvl = 1;
	while((rand() % 2) < 0.5 && lvl < MAX_HEIGHT) {
		lvl++;
	}
	return lvl;
}

void* searchSkipList(Skiplist *list, void* I) {
	char* failure = "not_found";
	Node * x = list->head;

	// loop invariant: x->item < I
	for(int i = list->max_level-1; i >= 0; i--) {
		while(x->next[i] != NULL && list->compare(x->next[i]->item, I) < 0) {
			x = x->next[i];
		}
	}
	// x->item < I <= x->next[1]->item
	x = x->next[0];
	if(x != NULL) {

		if(list->compare(x->item, I) == 0) {
			return x->item;
		} else {
			return failure;
		}
	}
	return failure;
}

void* SkipList_get_elem(Skiplist* list, unsigned long i) {
	int position = 0;
	bool found = false; 
	Node *search = list->head->next[0];
	if(list->head == NULL) {
		fprintf(stderr, "SkipList_get_elem: Skiplist parameter cannot be NULL");
		exit(EXIT_FAILURE);
	}
	if(i < 0) {
		fprintf(stderr, "SkipList_get_elem: index is out of bounds");
		exit(EXIT_FAILURE);
	}
	while(search != NULL) {
		if(position != i) {
			position++;
			search = search->next[0];
		} else {
			return search->item;
		}
	}
	exit (EXIT_FAILURE);
}

Node* createNode(void * I, int level) {
		Node *snode = (Node*) malloc (sizeof(Node)); 
		snode->size = level;
		snode->item = I;
		snode->next = (Node**)malloc ((sizeof(Node*))*level);
		for(int i = level; i <= 0; i--) {
			snode->next[i] = NULL;
		}
	return snode;
}

Skiplist* Skiplist_init(Skiplist *list, int (*compare)(void*, void*)) {
	Node *sentinel = (Node*)malloc (sizeof(Node));
	list->head = sentinel ;
	sentinel->item = NULL;
	sentinel->size = MAX_HEIGHT;
	sentinel->next = (Node **)malloc (sizeof(Node*)*(MAX_HEIGHT));
	list->compare = compare;
	list->max_level = 0;
	return list;
}

int Skiplist_is_empty(Skiplist*list) {
	if(list->head->next[0] == NULL) {
		return 1;
	}
	return 0;
}

void deleteNode(Node *snode) {
	if(snode != NULL) {
		if(snode->next != NULL) {
			free(snode->next);
		}
		free(snode);
	}
}

void deleteSkipList(Skiplist *list) {
	if(list->head != NULL) {
		Node *prec = list->head->next[0];
		if(prec != NULL) {
			Node* suc = prec->next[0];
			while(suc != NULL) {
				deleteNode(prec);
				prec = suc;
				suc = prec->next[0];
			}
		deleteNode(prec);
		}
		free(list->head);
	}
}
