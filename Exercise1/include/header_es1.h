#pragma once

typedef struct _SortedArray SortedArray;
/*
Sorted array's definition.
*/

typedef int (*SortedArrayCmp) (void*, void*);
/*
Pointer to function that compares element in the sorted array.
*/

typedef void (*SortedArrayQuicksort) (void*, int, int);
/*
Pointer to quicksort's function.
*/

typedef void (*SortedArrayInsertsort) (void*);
/*
Pointer to insertion sort's function.
*/

/*
Input: a pointer to compare function.
Output: a new sorted array. 
*/
SortedArray* sorted_array_new(SortedArrayCmp);


/*
Function frees the memory occupied by the sorted array.
Input: a sorted array.
Output: \
*/
void sorted_array_free(SortedArray* sa);


/*
Insert an element in sorted array.
Input: a sorted array and an element to insert. 
Output: a modified sorted array.
*/
void sorted_array_insert(SortedArray* sa, void* obj);


/*
Input: a sorted array.
Output: size of the sorted array.
*/
int sorted_array_size(SortedArray* sa);


/*
Swap the element at position i with the one at position j.
Input: a sorted array and two indexes.
Output: a sorted array modified.
*/
void sorted_array_swap(SortedArray* sa, int i, int j);


/*
Input: a sorted array and an index.
Output: return the element at position i.
*/
void* sorted_array_get(SortedArray* sa, int i);

/*
A binary search based function to find the position 
where item should be inserted in sa->array[first .... last ].
*/
int binarySerach(SortedArray* sa, void * item, int first, int last);

/*
Function sorts the array using insertion sort alghoritm whit randomized pivot.
Input: an array.
Output: the sorted array.
*/
void insertion_sort(SortedArray* sa);

/*
Function sorts the array using insertion sort alghoritm.
Input: an array.
Output: the sorted array.
*/
void insertion_sort_not_randomized(SortedArray*sa);

/*
Function sorts the array using quicksort alghoritm.
Input: an array and extreme indexes to sort.
Output: the sorted array.
*/
void quicksort(SortedArray* sa, int first, int last);

/*
Function that randomly extracts a pivot and swaps the values at the indices pivot and last.
Input: a sorted array and the extreme indexes' partition.
Output: a sorted array's partition.
*/
int randomized_partition(SortedArray* sa, int first, int last );

/*
Function creates a partition of sorted array.
Input: a sorted array and the extreme indexes' partition.
Output: a sorted array's partition.
*/
int partition(SortedArray* sa, int first, int last);
