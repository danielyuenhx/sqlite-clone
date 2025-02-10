#include <stdio.h>
#include <stdlib.h>
#include <BaseTsd.h>

typedef struct {
  char* buffer;
  size_t buffer_length; // unsigned datatype, only positive numberss
  SSIZE_T input_length; // similar to size_t, but with -1 for an error value
} InputBuffer;

InputBuffer* new_input_buffer() {
  InputBuffer* input_buffer = malloc(sizeof(InputBuffer));
  input_buffer->buffer = NULL;
  input_buffer->buffer_length = 0;
  input_buffer->input_length = 0;
  
  return input_buffer;
}

void clean_up_input_buffer(InputBuffer* input_buffer) {
  free(input_buffer->buffer); // getline() mallocates it if buffer is NULL, so we have to free
  free(input_buffer);
}