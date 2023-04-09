#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "header_es1.h"

#define INITIAL_CAPACITY 100

struct _SortedArray {
	void** array;
	int capacity;
	int size;
	SortedArrayCmp compare;
};


SortedArray* sorted_array_new(SortedArrayCmp compare) {

	SortedArray* result = (SortedArray*) malloc(sizeof(SortedArray));
	result->capacity = INITIAL_CAPACITY;
	result->array  = (void**) malloc (sizeof(void*) * result->capacity);
	result->size = 0;
	result->compare = compare;

	return result;
}

void sorted_array_free(SortedArray* sa) {
	free(sa-> array);
	free(sa);
}

void sorted_array_resize(SortedArray* sa, size_t memsize) {
  sa->capacity = memsize;
  sa->array = (void**) realloc(sa->array, sa->capacity*sizeof(void*));
}

void sorted_array_insert(SortedArray* sa, void* obj) {
	if(sa->capacity == sa->size){
    sorted_array_resize(sa, sa->capacity*2);
	}
	int j = sa->size;
	sa->array[j] = obj;
	sa->size++;
}

int binarySerach(SortedArray* sa, void * item, int first, int last) {
  if(last <= first) {
    if(sa->compare(item, sa->array[first])>0) {
      return first+1;
    } else {
      return first; 
    }
  }
  int mid = (first + last)/2;
  if(sa->compare(item, sa->array[mid]) == 0) {
    return mid+1;
  }
  if(sa->compare(item, sa->array[mid]) >= 0) {
    return binarySerach(sa, item, mid+1, last);
  }
  return binarySerach(sa, item, first, mid-1);
}

void insertion_sort(SortedArray* sa ) {
  int i, j, k, loc;
  void * selected; 
  for (i = 1; i < sorted_array_size(sa); i++) {
    j = i-1;
    selected = sa->array[i];
    loc = binarySerach(sa, selected, 0, j);
    while(j >= loc) {
      sa->array[j+1] = sa->array[j];
      j--;
    }
    sa->array[j+1] = selected;
  }
}

void insertion_sort_not_randomized(SortedArray*sa) {
  for(int i = 0; i < sorted_array_size(sa); i++) {
    int j = i;
    while(j > 0 && sa->compare(sa->array[j-1], sa->array[j]) > 0) {
      sorted_array_swap(sa, j-1, j);
      j--;
    }
  }
}

void quicksort(SortedArray* sa, int first, int last) {
  if(first < last) {
    int q = randomized_partition(sa, first, last);
    quicksort(sa, first, q-1);
    quicksort(sa, q+1, last);
  }
}

int randomized_partition(SortedArray* sa, int first, int last ) {
  srand(time(NULL));
  int n = rand();
  int pivot = (int) first + n% (last-first+1);
  sorted_array_swap(sa, last, pivot);
  return partition(sa, first, last);
}

int partition(SortedArray* sa, int first, int last) {
  int i = first - 1;
  for(int j = first; j <= last-1; j++) {
    if(sa->compare(sa->array[j], sa->array[last]) <= 0) {
      i++;
      sorted_array_swap(sa, i, j);
    }
  }
  sorted_array_swap(sa, i+1, last);
  return i+1;
}

void sorted_array_swap(SortedArray* sa, int i, int j) {
  void* sup = sa->array[i];
  sa->array[i] = sa->array[j];
  sa->array[j] = sup;
}


int sorted_array_size(SortedArray* sa) {
	return sa->size;
}

void* sorted_array_get(SortedArray* sa, int i) {
  return sa->array[i];
}
