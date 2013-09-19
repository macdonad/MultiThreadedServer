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


int
main()
{
  input_buffer = malloc(sizeof(char*) * INPUT_BUFFER_SIZE);
  fgets(input_buffer, INPUT_BUFFER_SIZE, stdin);
  return 0;
}
