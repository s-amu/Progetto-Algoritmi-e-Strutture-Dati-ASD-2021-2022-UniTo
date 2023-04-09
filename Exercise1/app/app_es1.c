#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "header_es1.h"

#define LEN_BUF 1024
enum { NS_PER_SECOND = 1000000000 };

// Defines the type of records read from file.
typedef struct {
  int id;
  char* field1;
  int field2;
  float field3;
}Record;

// Options accepted by this program.
typedef struct {
  SortedArrayCmp cmp_function;
  SortedArrayQuicksort quicksort_fun;
  SortedArrayInsertsort insertsort_fun;
  char const* file;
}Options;

int compare_first_field(Record* rec1, Record* rec2) {
  return strcmp(rec1->field1, rec2->field1);
}

int compare_second_field(Record* rec1, Record* rec2) {
  return (rec1->field2 - rec2->field2);
}

int compare_third_field(Record* rec1, Record* rec2) {
  return (rec1->field3 - rec2->field3);
}

Options parse_options(int argc, const char* argv[]) {
  if(argc != 4) {
    printf("Arguments error\n");
    printf(" app_es1 < -1 | -2 | -3> <quicksort | insertion_sort> <filename>\n");
    printf("    -1: sort according to the first field ascending order\n");
    printf("    -2: sort according to the second field ascending order\n");
    printf("    -3: sort according to the third field ascending order\n");

    exit(EXIT_FAILURE);
  }

  Options options;

  if(!strcmp(argv[1], "-1")) {
    options.cmp_function = (SortedArrayCmp) compare_first_field;
  } else if(!strcmp(argv[1], "-2" )) {
    options.cmp_function = (SortedArrayCmp) compare_second_field;
  } else if(!strcmp(argv[1], "-3")) {
    options.cmp_function = (SortedArrayCmp) compare_third_field;
  } else {
    printf("Arguments error\n");
    printf("app_es1 < -1 | -2 | -3> <quicksort | insertion_sort> <filename>\n");
    printf("    -1: sort according to the first field ascending order\n");
    printf("    -2: sort according to the second field ascending order\n");
    printf("    -3: sort according to the third field ascending order\n");
    exit(EXIT_FAILURE);
  }

  if(!strcmp(argv[2], "quicksort")) {
    options.quicksort_fun = (SortedArrayQuicksort) quicksort;
    options.insertsort_fun = NULL;
  } else if(!strcmp(argv[2], "insertion_sort")) {
    options.quicksort_fun = NULL;
    options.insertsort_fun = (SortedArrayInsertsort) insertion_sort;
  } else {
    printf("Arguments error\n");
    printf("app_es1 < -1 | -2 | -3> <quicksort | insertion_sort> <filename>\n");
    printf("    -1: sort according to the first field ascending order\n");
    printf("    -2: sort according to the second field ascending order\n");
    printf("    -3: sort according to the third field ascending order\n");
    exit(EXIT_FAILURE);
  }
  options.file = argv[3];
  return options;
}

void free_data(SortedArray* sa) {
  for(int i = 0; i < sorted_array_size(sa); i++) {
    Record* rec = sorted_array_get(sa, i);
    free(rec->field1);
    free(rec);
  }
  sorted_array_free(sa);
}

void load_data(SortedArray* sa, const char* filename) {
  FILE* file = fopen(filename, "r");
  int id;
  char field1[LEN_BUF];
  int field2;
  double field3;
  int line = 0;
  while(!feof(file)) {
    Record* record = (Record*) malloc(sizeof(Record));    
    int n = fscanf(file, "%d,%1024[^,],%d,%lf\n", &id, field1, &field2, &field3);
    line++;
    if(n == 4) {
      record->id = id;
      for(int l = 0; field1[l] != '\0'; l++) {
        if(field1[l] >= 'A' && field1[l] <= 'Z') {
          field1[l] = field1[l] + 32;
          record->field1 = strndup(field1, LEN_BUF);
        }
      }
      record->field1 = strndup(field1, LEN_BUF);
      record->field2 = field2;
      record->field3 = field3;
      sorted_array_insert(sa, record);
    } else {
      printf("Error while reading file at line: %d\n", line);
      break; 
    }
  }
  fclose(file);
}

void print_array(SortedArray* sa) {
  for(int i = 0; i < sorted_array_size(sa); i++) {
    Record* rec = sorted_array_get(sa, i);
    printf("id:  %5d \t     field1:  %15s \t     field2:  %10d \t     field3:  %10f\n", rec->id, rec->field1, rec->field2, rec->field3);
  }
}

long sub_timespec(struct timespec start , struct timespec stop , struct timespec t_delta) {
  long time_t1_nsec = start.tv_sec *NS_PER_SECOND + start.tv_nsec;
  long time_t2_nsec = stop.tv_sec *NS_PER_SECOND + stop.tv_nsec;
  long time_delta_nsec = time_t2_nsec - time_t1_nsec; 
  return time_delta_nsec;
}

void print_time(struct timespec start , struct timespec finish , struct timespec delta) {
  printf("The algorithm takes %ld nanoseconds\n", sub_timespec(start, finish, delta));
}

int main(int argc, const char* argv[]) {
  struct timespec start, stop, delta;
  Options options = parse_options(argc, argv);
  SortedArray* array = sorted_array_new(options.cmp_function);
  load_data(array, options.file);
  clock_gettime(CLOCK_REALTIME, &start);
  printf("Initial time [nsec]: %ld \n", start.tv_sec *NS_PER_SECOND + start.tv_nsec);
  if(options.quicksort_fun != NULL) {
    options.quicksort_fun(array, 0, sorted_array_size(array)-1);
  } else {
    options.insertsort_fun(array);
  }
  clock_gettime(CLOCK_REALTIME, &stop);
  printf("Final time [nsec]: %ld \n", stop.tv_sec *NS_PER_SECOND + stop.tv_nsec);
  print_array(array);
  print_time(start, stop, delta);
  free_data(array);
  return 0;
}
