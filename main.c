#include <stdio.h>
#include <stdbool.h>
#include "structs.c"

void read_input(InputBuffer* input_buffer) {
  // read the line from stdin into the input buffer
  SSIZE_T bytes_read = getline(&input_buffer->buffer, &input_buffer->buffer_length, stdin);
  if (bytes_read <= 0) {
    printf("Error reading input\n");
    exit(EXIT_FAILURE);
  }
  // remove trailing newline
  input_buffer->input_length = bytes_read - 1; // since bytes_read may be less than buffer_length, we store this
  input_buffer->buffer[bytes_read - 1] = 0;

  to_lower(input_buffer->buffer);
}

int main(int argc, char* argv[]) {
  InputBuffer* input_buffer = new_input_buffer();

  while (true) {
    print_prompt();
    read_input(input_buffer);
  }
  return 0;
}