#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


#define INPUT_BUFFER_SIZE 1024

/**
 * Input buffer
 */
char* input_buffer;

/**
 * Global access time
 */

/**
 * Global request counter
 */
int total_requests;

/**
 * Handle a C-c
 */
void handle_sigint(int sig);

/**
 * Retrieve file
 */
void* worker_function(void* arg);

int
main()
{
  signal(SIGINT, handle_sigint);
  while(1) {
    input_buffer = malloc(sizeof(char*) * INPUT_BUFFER_SIZE);
    fgets(input_buffer, INPUT_BUFFER_SIZE, stdin);
    int filename_size = strlen(input_buffer);
    char* filename = malloc(sizeof(char*) * filename_size);
    memcpy(filename, input_buffer, filename_size);
    pthread_t worker_thread;
    pthread_create(&worker_thread, NULL, worker_function, filename);
  }  
  return 0;
}


/**
 * Handle a C-c
 */
void
handle_sigint(int sig) 
{
  printf("SIGNALLIN!\n");
  exit(0);
}

void* 
worker_function(void* arg) 
{
  total_requests++;
  /* insert time crap here */
  char* filename = (char*) arg;
  int rand_val = rand() % 10;
  sleep((rand_val >= 2) ? 1 : 7 + (rand() % 4));
  printf("Retrieved: %s\n", filename);
  free(filename);
  return NULL;
}
