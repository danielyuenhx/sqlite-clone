#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "structs.c"
#include "utils.c"

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

MetaCommandResult do_meta_command(InputBuffer* input_buffer) {
  if (strcmp(input_buffer->buffer, ".exit") == 0) {
    clean_up_input_buffer(input_buffer);
    printf("bye");
    exit(EXIT_SUCCESS);
  } else {
    return META_COMMAND_UNRECOGNISED_COMMAND;
  }
}

PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement) {
  if (strncmp(input_buffer->buffer, "insert", 6) == 0) {
    statement->type = STATEMENT_INSERT;
    int args_assigned = sscanf(
      input_buffer->buffer, "insert %d %s %s", &statement->row_to_insert->id, 
      statement->row_to_insert->username, statement->row_to_insert->email
    );
    if (args_assigned < 3) {
      return PREPARE_SYNTAX_ERROR;
    };
    
    return PREPARE_SUCCESS;
  } else if (strncmp(input_buffer->buffer, "select", 6) == 0) {
    statement->type = STATEMENT_SELECT;
    return PREPARE_SUCCESS;
  }
  return PREPARE_UNRECOGNISED_STATEMENT;
}

void execute_statement(Statement* statement) {
  printf("Executing");
}

int main(int argc, char* argv[]) {
  InputBuffer* input_buffer = new_input_buffer();

  while (true) {
    print_prompt();
    read_input(input_buffer);
    
    // meta commands starting with '.'
    if (input_buffer->buffer[0] == '.') {
      switch (do_meta_command(input_buffer)) {
        case (META_COMMAND_SUCCESS):
          continue;
        case (META_COMMAND_UNRECOGNISED_COMMAND):
          printf("unrecognised meta command: %s\n", input_buffer->buffer);
          continue;
      }
    }

    Statement statement;
    switch (prepare_statement(input_buffer, &statement)) {
      case (PREPARE_SUCCESS):
        break;
      case (PREPARE_UNRECOGNISED_STATEMENT):
        printf("Unrecogniseed keyword at start of '%s'.\n", input_buffer->buffer);
        continue;
    }

    execute_statement(&statement); // this is the virtual machine
    printf("Executed.\n");
  }
  return 0;
}