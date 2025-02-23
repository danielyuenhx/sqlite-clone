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

/*
define keyword is handled by the preprocessor. to define macro constants
there is no typing, it is directly substituted in text. therefore, cant be debugged/type checked during compilation
global, and not allocated any memory. since its just a substitution, it can be faster in some cases
*/ 
#define COLUMN_USERNAME_SIZE 32 
#define COLUMN_EMAIL_SIZE 255

typedef struct {
  uint32_t id;
  char username[COLUMN_USERNAME_SIZE];
  char email[COLUMN_EMAIL_SIZE];
} Row;

#define size_of_attribute(struct, attribute) sizeof(((struct*)0)->attribute)

const uint32_t ID_SIZE = size_of_attribute(Row, id);
const uint32_t USERNAME_SIZE = size_of_attribute(Row, username);
const uint32_t EMAIL_SIZE = size_of_attribute(Row, username);
const uint32_t ID_OFFSET = 0;
const uint32_t USERNAME_OFFSET = ID_OFFSET + ID_SIZE;
const uint32_t EMAIL_OFFSET = USERNAME_OFFSET + USERNAME_SIZE;
const uint32_t ROW_SIZE = ID_SIZE + USERNAME_SIZE + EMAIL_SIZE;

const uint32_t PAGE_SIZE = 4096;
#define TABLE_MAX_PAGES 100
const uint32_t ROWS_PER_PAGE = PAGE_SIZE/ROW_SIZE;
const uint32_t TABLE_MAX_ROWS = ROWS_PER_PAGE * TABLE_MAX_PAGES;

typedef struct {
  uint32_t num_rows;
  void* pages[TABLE_MAX_PAGES];
} Table;