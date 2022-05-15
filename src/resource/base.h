#ifndef MEMO_RESOURCE_BASE_H
#define MEMO_RESOURCE_BASE_H

namespace memo {
namespace resource {

class Base
{
public:
  Base() {}
  virtual ~Base() {}

  virtual void* allocate(std::size_t n) = 0;
  virtual void deallocate(void* p, std::size_t n) = 0;
};

}
}

#endif // MEMO_RESOURCE_BASE_H
