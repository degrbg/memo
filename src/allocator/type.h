#ifndef MEMO_ALLOCATOR_TYPE_H
#define MEMO_ALLOCATOR_TYPE_H

#include <memory>
#include <type_traits>

#include <strategy/base.h>

namespace memo {
namespace allocator {

template <typename T,
    typename Strategy,
    typename std::enable_if<
    std::is_base_of<strategy::Base<typename Strategy::resource_type>,
    Strategy>::value, bool>::type = true>
class Type
{
public:
  using value_type = T;

  Type() :
      ts_{ sizeof(T) },
      strategy_{ std::make_shared<Strategy>() }
  {}

  Type(const Type& other) :
      ts_{ other.ts_ },
      strategy_{ other.strategy_ }
  {}

  template <typename U>
  Type(const Type<U, Strategy>& other) :
      ts_{ sizeof(T) },
      strategy_{ other.strategy_ }
  {}

  template <typename U>
  bool operator==(const Type<U, Strategy>& other)
  {
    return strategy_ == other.strategy_;
  }

  template <typename U>
  bool operator!=(const Type<U, Strategy>& other)
  {
    return !(*this == other);
  }

  T* allocate(std::size_t n)
  {
    auto p = strategy_->allocate(ts_ * n);
    auto tp = static_cast<T*>(p);
    return tp;
  }

  void deallocate(T* tp, std::size_t n)
  {
    auto p = static_cast<void*>(tp);
    strategy_->deallocate(p, ts_ * n);
  }

  void shrink_to_fit()
  {
    strategy_->shrink_to_fit();
  }

  void release()
  {
    strategy_->release();
  }

private:
  const std::size_t ts_;
  std::shared_ptr<Strategy> strategy_;
};

}
}

#endif // MEMO_ALLOCATOR_TYPE_H
