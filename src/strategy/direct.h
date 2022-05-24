#ifndef MEMO_STRATEGY_DIRECT_H
#define MEMO_STRATEGY_DIRECT_H

#include <strategy/base.h>

namespace memo {
namespace strategy {

template <typename Resource>
class Direct : public Base<Resource>
{
public:
  Direct() {}
  ~Direct() {}

  void shrink_to_fit() override {}

protected:
  void* strategy_allocate(std::size_t n) override
  {
    return this->resource_allocate(n);
  }

  void strategy_deallocate(void* p, std::size_t n) override
  {
    this->resource_deallocate(p, n);
  }

  void strategy_release() override {}
};

}
}

#endif // MEMO_STRATEGY_DIRECT_H
