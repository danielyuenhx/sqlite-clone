#include <stdio.h>
#include <ctype.h>

void print_prompt() {
  printf("db > ");
}

void to_lower(char* str) {
  for ( ; *str; ++str) *str = tolower(*str);
}