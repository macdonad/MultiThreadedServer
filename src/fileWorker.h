// fileWorker.h

#ifndef _FILE_WORKER_H_
#define _FILE_WORKER_H_

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
  double time_taken;
  char* filename;
  bool active;
  struct _file_worker_t* peer;
};


/**
 * File worker type.
 */
typedef struct _file_worker_t file_worker_t;


/**
 * Create a new file worker
 */
file_worker_t*
file_worker_new(char* file, file_worker_t* peer);

/**
 * Free a file worker
 */
void
file_worker_free(file_worker_t* this);

/**
 * Kick off a file worker thread
 */
int
file_worker_start(file_worker_t* this);


/**
 * Join a worker thread
 */
int
file_worker_join(file_worker_t* this);

#endif

/* fileWorker.h ends here */
