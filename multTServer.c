// multTServer.c

#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "multTServer.h"


/* **************************************************************
 * Types
 * ************************************************************** */


/**
 * File worker struct type.
 *
 * ID: Cooresponding thread ID
 * FILENAME: Retrieval job file
 * ACTIVE: False if the retrieval completed or failed
 * PEER: Pointer to the other most recent worker created.
 */
struct _file_worker_t
{
  pthread_t id;
  char* filename;
  bool active;
  struct _file_worker_t* peer;
};


/**
 * File worker type.
 */
typedef struct _file_worker_t file_worker_t;


/* **************************************************************
 * Globals
 * ************************************************************** */


/**
 * Input buffer
 */
char* input_buffer;


/**
 * Global access time
 */
/* TODO */


/**
 * Global request counter
 */
int total_requests;


/**
 * The most recently started worker.
 */
file_worker_t* last_worker;


/**
 * Main
 */
int
main()
{
  signal(SIGINT, handle_sigint);
  input_buffer = ARRLOC(char*,  INPUT_BUFFER_SIZE);
  while(1) {
    fgets(input_buffer, INPUT_BUFFER_SIZE, stdin);
    char* newline_pos = strchr(input_buffer, '\n');
    if (newline_pos != NULL) *newline_pos = '\0';
    int filename_size = strlen(input_buffer);
    file_worker_t* worker = malloc(sizeof(*worker));
    worker->filename = ARRLOC(char*, filename_size);
    worker->active = true;
    memcpy(worker->filename, input_buffer, filename_size);
    worker->peer = last_worker;
    pthread_create(&(worker->id), NULL, worker_function, worker);
    last_worker = worker;
  }
  return 0;
}


/**
 * Handle a C-c
 *
 * On SIGINT, join all worker threads, print stats, and exit.
 */
void
handle_sigint(int sig)
{
  printf("\nBeginning shutdown\n");
  file_worker_t* worker = last_worker;
  while (worker && worker->peer)
    {
      pthread_join(worker->id, (void*)NULL);
      file_worker_t* current = worker;
      worker = worker->peer;
      free(current);
    }
  free(input_buffer);
  exit(0);
}


/**
 * Worker function
 * Each worker will retrieve a file then report completion
 *
 * ARG: a pointer to this file_worker_t
 */
void*
worker_function(void* arg)
{
  total_requests++;
  /* insert time crap here */
  file_worker_t* this = (file_worker_t*) arg;
  int rand_val = rand() % 10;
  sleep((rand_val >= 2) ? 1 : 7 + (rand() % 4));
  this->active = false;
  printf("Thread: [%u] retrieved: %s\n",
	 // this is silly
	 (unsigned int)(uintptr_t)(this->id), this->filename);
  free(this->filename);
  return NULL;
}
