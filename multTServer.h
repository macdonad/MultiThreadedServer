// multTServer.h

#ifndef _MULT_T_SERVER_H
#define _MULT_T_SERVER_H

/* **************************************************************
 * Macros
 * ************************************************************** */


/**
 * Filename input buffer size
 */
#define INPUT_BUFFER_SIZE 1024


/**
 * Allocate memory for an TYPE array of given SIZE
 */
#define ARRLOC(type, size) calloc(size, sizeof(type))


/* **************************************************************
 * Prototypes
 * ************************************************************** */


/**
 * Handle a C-c
 */
void handle_sigint(int sig);


/**
 * Retrieve file
 */
void* worker_function(void* arg);


#endif /* _MULT_T_SERVER_H */

/* multTServer.h ends here */
