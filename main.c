#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

#define THREAD_RANGE 100
#define SORT_MAX 1000

struct args_t_struct {
  int id;
  int to_sort[SORT_MAX];
};

void *execution(void *tmp) {
  double time_spent = 0.0;
  clock_t begin = clock();

  struct args_t_struct *args = (struct args_t_struct *) tmp;
  
  for (int i = 0; i < SORT_MAX; i++) {
    for (int j = i + 1; j < SORT_MAX; j++) {
      if (args->to_sort[i] > args->to_sort[j]) {
        int tmp = args->to_sort[i];
        args->to_sort[i] = args->to_sort[j];
        args->to_sort[j] = tmp;
      }
    }
  }

  clock_t end = clock();
  time_spent += (double) (end - begin) / CLOCKS_PER_SEC;
  
  printf("[THREAD] ID #%d / WAIT_TIME %fs\n\n", args->id, time_spent);
}

int main() {
  pthread_t lines[THREAD_RANGE];

  int exec;

  struct args_t_struct *args;

  srand(time(NULL));

  for (int i = 0; i < THREAD_RANGE; i++) {

    struct args_t_struct *args = malloc(sizeof(struct args_t_struct));

    for (int j = 0; j < SORT_MAX; j++) {
      args->to_sort[j] = (rand() % 1000);
    }
    
    args->id = i;

    exec = pthread_create(&lines[i], NULL, execution, (void *) args);
  }

  pthread_exit(NULL);
}