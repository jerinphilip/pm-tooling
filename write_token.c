#include <stdio.h>

#define BUFFER_SIZE 1024
#define TOKEN_BYTES 256
#define DEVINFO_BYTES (8 * 1024 * 1024)

int main(int argc, char **argv) {
  FILE *token_file = fopen(argv[1], "rb");
  char token[BUFFER_SIZE];
  int length = 0;
  char c;
  while (!feof(token_file) && length < TOKEN_BYTES) {
    c = fgetc(token_file);
    token[length] = c;
    ++length;
  }
  fclose(token_file);

  fprintf(stderr, "Read token: %d bytes\n", length);
  fprintf(stderr, "%s\n", token);

  int offset = DEVINFO_BYTES - TOKEN_BYTES;

  FILE *devinfo = fopen(argv[2], "wb+");

  int position = 0;
  while (position < offset) {
    fputc(0, devinfo);
    ++position;
  }

  for (size_t i = 0; i < length; i++) {
    fputc(token[i], devinfo);
  }

  fclose(devinfo);
  return 0;
}
