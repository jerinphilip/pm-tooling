#include "Mmap.hh"
#include <fcntl.h>
#include <stdexcept>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

namespace pm {

Mmap::Mmap(const std::string &filepath) {
  fd_ = open(filepath.c_str(), O_RDONLY);
  if (fd_ == -1) {
    throw std::runtime_error("Failed to open file: " + filepath);
  }

  struct stat st;
  if (fstat(fd_, &st) == -1) {
    close(fd_);
    throw std::runtime_error("Failed to get file size: " + filepath);
  }
  size_ = st.st_size;

  data_ = mmap(nullptr, size_, PROT_READ, MAP_PRIVATE, fd_, 0);
  if (data_ == MAP_FAILED) { // NOLINT
    close(fd_);
    throw std::runtime_error("Failed to mmap file: " + filepath);
  }
}

Mmap::~Mmap() {
  if (data_ != nullptr) {
    munmap(data_, size_);
  }
  if (fd_ != -1) {
    close(fd_);
  }
}

Mmap::Mmap(Mmap &&from) noexcept
    : fd_(from.fd_), data_(from.data_), size_(from.size_) {
  reset();
};

Mmap &Mmap::operator=(Mmap &&from) noexcept {
  if (this == &from) {
    return *this;
  }
  reset();
  consume(from);
  return *this;
}

void Mmap::consume(Mmap &from) {
  fd_ = (from.fd_);
  data_ = (from.data_);
  size_ = (from.size_);
  from.reset();
}

void Mmap::reset() {
  fd_ = -1;
  data_ = nullptr;
  size_ = 0;
}
} // namespace pm
