#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "header_es2.h"

#define LEN_BUF 1024

enum { NS_PER_SECOND = 1000000000 };

typedef struct {
	char const* filename_dictionary;
	char const* filename_correct_me;
}Options; 

int compare_item(void * item1, void * item2) {
	return strcmp((char*)item1, (char*)item2);
}

/* Lettura dei file da terminale (devono essere tre : app_es2 , "dizionario" e "file da correggere")*/
Options read_file(int argc, const char * argv[]) {
	if(argc != 3) {
		printf("Argument error\n");
		printf(" app_es2 and enter the name of the file to be corrected and the dictionary of words used\n");
		printf(" app_es2 | <filename_to_corrected> | <filename_dictionary> ");
		exit(EXIT_FAILURE);
	}
	Options options;

	options.filename_dictionary = argv[1];
	options.filename_correct_me = argv[2];
	return options;
}

Skiplist* load_data(Skiplist *list, const char * filename_dictionary) {
	FILE *file = fopen(filename_dictionary, "r");
	int line = 0;
	char *words;

	while(!feof(file)) {
		words = (char*)malloc(sizeof(char)*LEN_BUF);
		int read = fscanf(file, "%s", words);
			if(words[0] >= 'A' && words[0] <= 'Z') {
			words[0] = words[0] + 32;
		}
		line ++;

		if(read) {
			list = insertSkipList(list , words);
		} else {
			printf("Error while reading file");
			break ; 
		}
	}
	fclose(file);
	free(words);
	return list;
}

void search_words(Skiplist *list, const char* filename_correct_me) {
	FILE *file_to_correct = fopen(filename_correct_me, "r");
	char *word; 
	char *words_to_correct;

	fprintf(stderr, "Words to correct (not present in the input dictionary):\n\n");
	while(!feof(file_to_correct)) {
		word = (char*)malloc(sizeof(char)*LEN_BUF);
		words_to_correct = (char*)malloc(sizeof(char)*LEN_BUF);
		fscanf(file_to_correct, "%s", word);
		for(int i = 0; word[i] != '\0'; i++) {
			if(word[i] >= 'A' && word[i] <= 'Z') {
				words_to_correct[i] = word[i] + 32;
			} else if(word[i] >= 'a' && word[i] <= 'z') {
				words_to_correct[i] = word[i];
			} else {
				break; 
			}
		}
		if(list->compare(words_to_correct, searchSkipList(list, words_to_correct)) != 0) {
			fprintf(stderr, "%s\n", (char*)words_to_correct);
		}
	}
}

long sub_timespec(struct timespec start, struct timespec stop, struct timespec t_delta) {
  long time_t1_nsec = start.tv_sec *NS_PER_SECOND + start.tv_nsec;
  long time_t2_nsec = stop.tv_sec *NS_PER_SECOND + stop.tv_nsec;
  long time_delta_nsec = time_t2_nsec - time_t1_nsec; 
  return time_delta_nsec;
}

void print_time(struct timespec start, struct timespec finish, struct timespec delta) {
  printf("The algorithm takes %ld nanoseconds\n", sub_timespec(start, finish, delta));
}

int main(int argc, const char* argv[]) {
	struct timespec start, stop, delta;
	Options options = read_file(argc, argv);
	Skiplist list;
	Skiplist_init(&list, compare_item);
  clock_gettime(CLOCK_REALTIME, &start);
  printf("MAX_HEIGHT: %d\n", MAX_HEIGHT);
  printf("Initial time [nsec]: %ld \n", start.tv_sec *NS_PER_SECOND + start.tv_nsec);
	load_data(&list, options.filename_dictionary);
	search_words(&list , options.filename_correct_me);
  clock_gettime(CLOCK_REALTIME,&stop);
  printf("Final time [nsec]: %ld \n", stop.tv_sec *NS_PER_SECOND + stop.tv_nsec);
  print_time(start, stop, delta);
  deleteSkipList(&list);
  return 0;
}
