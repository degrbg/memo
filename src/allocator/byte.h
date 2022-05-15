#ifndef MEMO_ALLOCATOR_BYTE_H
#define MEMO_ALLOCATOR_BYTE_H

#include <memory>
#include <type_traits>

#include <strategy/base.h>

namespace memo {
namespace allocator {

template <typename Strategy,
    typename std::enable_if<
    std::is_base_of<strategy::Base<typename Strategy::resource_type>,
    Strategy>::value, bool>::type = true>
class Byte
{
public:
  Byte() :
    strategy_{ std::make_shared<Strategy>() }
  {}

  Byte(const Byte& other) {}

  void* allocate(std::size_t n)
  {
    auto p = strategy_->allocate(n);
    return p;
  }

  void deallocate(void* p, std::size_t n)
  {
    strategy_->deallocate(p, n);
  }

  bool operator==(const Byte& other)
  {
    return strategy_ == other.strategy_;
  }

  bool operator!=(const Byte& other)
  {
    return !(*this == other);
  }

private:
  std::shared_ptr<Strategy> strategy_;
};

}
}

#endif // MEMO_ALLOCATOR_BYTE_H
