#include "Mmap.hh"
#include <cstdio>
#include <string>

int main(int argc, char **argv) {
  std::string fpath = argv[1];
  pm::Mmap mmap(fpath);
  char *data = reinterpret_cast<char *>(mmap.data());
  for (size_t i = 0; i < mmap.size(); i++) {
    if (*data != 0) {
      fputc(*data, stdout);
    }
    ++data;
  }
  fputc('\n', stdout);
  return 0;
}
