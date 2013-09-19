// multTServer.c

#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <stdbool.h>
#include <sys/time.h>

#include "multTServer.h"


/* **************************************************************
 * File worker type
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
  time_t time_taken;
  char* filename;
  bool active;
  struct _file_worker_t* peer;
};


/**
 * File worker type.
 */
typedef struct _file_worker_t file_worker_t;


/* **************************************************************
 * File worker methods
 * ************************************************************** */

/**
 * Create a new file worker
 */
file_worker_t* 
file_worker_new(char* file, file_worker_t* peer) 
{
  int filename_size = strlen(file);
  file_worker_t* worker = malloc(sizeof(*worker));
  worker->filename = ARRLOC(char*, filename_size);
  worker->active = true;
  memcpy(worker->filename, file, filename_size);
  worker->peer = peer;
  return worker;
}


/**
 * Kick off a file worker thread
 */
int 
file_worker_start(file_worker_t* this) 
{
  return pthread_create(&(this->id), NULL, worker_function, this);
}


/**
 * Join a worker thread
 */
int 
file_worker_join(file_worker_t* this)
{
  if (this && this->id) return pthread_join(this->id, (void*)NULL);
  else return -1;
}


/**
 * Free a file worker
 */
void
file_worker_free(file_worker_t* this)
{
  if (this) {
    if (this->filename && *(this->filename)) free(this->filename);
    free(this);
  }
}


bool 
file_worker_has_peer(file_worker_t* this)
{
  return (this && this->peer);
}


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
  // resource setup
  signal(SIGINT, handle_sigint);
  input_buffer = ARRLOC(char*,  INPUT_BUFFER_SIZE);
  
  // main server loop
  while(true) {
    read_filename();
    file_worker_t* worker = file_worker_new(input_buffer, last_worker);

    ON_ERROR(file_worker_start(worker)) 
      {
	printf("Error starting worker for \"%s\"\n", 
	       (worker && worker->filename) ? worker->filename : "unknown");
	file_worker_free(worker);
      } 
    else 
      {
	last_worker = worker;
      }
  }
  return 0;
}


/**
 * Read from stdin into the input_buffer
 */
void
read_filename(void) 
{
  fgets(input_buffer, INPUT_BUFFER_SIZE, stdin);
  char* newline_pos = strchr(input_buffer, '\n');
  if (newline_pos != NULL) *newline_pos = '\0';
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

  while (file_worker_has_peer(worker))
    {
      ON_ERROR(file_worker_join(worker)) 
	{
	  printf("Error joining worker for \"%s\"\n", 
		 (worker && worker->filename) ? worker->filename : "unknown");
	  
	}
      file_worker_t* current = worker;
      worker = worker->peer;
      file_worker_free(current);
    }
  
  /* **************************************************************
   * TODO: Print usage stats here
   * ************************************************************** */

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
  /* **************************************************************
   * TODO: increase total recieve count
   * ************************************************************** */
  
  
  /* **************************************************************
   * TODO: Start time
   * ************************************************************** */
  
  file_worker_t* this = (file_worker_t*) arg;
  int rand_val = rand() % 10;
  
  sleep((rand_val >= 2) ? 1 : 7 + (rand() % 4));
  
  this->active = false;
  
  printf("Thread: [%u] retrieved: %s\n",
	 // this is silly
	 (unsigned int)(this->id), this->filename);
  
  /* **************************************************************
   * TODO:Record total time
   * ************************************************************** */
  
  return NULL;
}
