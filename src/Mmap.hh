
#include <string>

namespace pm {
class Mmap {
public:
  explicit Mmap(const std::string &filepath);
  ~Mmap();

  void *data() const { return data_; }
  size_t size() const { return size_; }

  // Disable copy and assignment
  Mmap(const Mmap &) = delete;
  Mmap &operator=(const Mmap &) = delete;

  Mmap(Mmap &&from) noexcept;

  Mmap &operator=(Mmap &&from) noexcept;

private:
  void consume(Mmap &from);
  void reset();

  int fd_ = -1;
  void *data_ = nullptr;
  size_t size_ = 0;
};
} // namespace pm
