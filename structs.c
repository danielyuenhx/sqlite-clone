#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
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

typedef enum {
  META_COMMAND_SUCCESS,
  META_COMMAND_UNRECOGNISED_COMMAND,
} MetaCommandResult;

typedef enum { 
  PREPARE_SUCCESS, 
  PREPARE_SYNTAX_ERROR,
  PREPARE_UNRECOGNISED_STATEMENT,
} PrepareResult;

typedef enum { 
  STATEMENT_INSERT, 
  STATEMENT_SELECT 
} StatementType;

typedef struct {
  StatementType type;
  Row row_to_insert;
  Row row_to_select;
} Statement;

#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 255

typedef struct {
  uint32_t id;
  char username[COLUMN_USERNAME_SIZE];
  char email[COLUMN_EMAIL_SIZE];
} Row;