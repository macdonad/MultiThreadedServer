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
 * Get rid of cast warning on OSX
 */
#ifdef __APPLE__
#define CAST_UNSIGNED_INT(expr) ((unsigned int)(uintptr_t)(expr))
#else
#define CAST_UNSIGNED_INT(expr) ((unsigned int)(expr))
#endif

/**
 * Allocate memory for an TYPE array of given SIZE
 */
#define ARRLOC(type, size) calloc(size, sizeof(type))

#define ON_ERROR(expr) if(expr != 0)
/* **************************************************************
 * Prototypes
 * ************************************************************** */

/**
 * Read the fileanem
 */
void read_filename(void);

/**
 * Handle a C-c
 */
void handle_sigint(int sig);


/**
 * Retrieve file
 */
void* worker_function(void* arg);

/**
 * Print server statistics
 */
void print_server_stats(int worker_count, double total_time_taken);

#endif /* _MULT_T_SERVER_H */

/* multTServer.h ends here */
