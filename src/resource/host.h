#ifndef MEMO_RESOURCE_HOST_H
#define MEMO_RESOURCE_HOST_H

#include <cstdlib>

#include <resource/base.h>

namespace memo {
namespace resource {

class Host : public Base
{
public:
  Host() {}
  ~Host() {}

  void* allocate(std::size_t n) override
  {
    return std::malloc(n);
  }

  void deallocate(void* p, std::size_t n) override
  {
    std::free(p);
  }
};

}
}

#endif // MEMO_RESOURCE_HOST_H
