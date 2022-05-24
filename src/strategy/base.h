#ifndef MEMO_STRATEGY_BASE_H
#define MEMO_STRATEGY_BASE_H

#include <type_traits>

#include <resource/base.h>

namespace memo {
namespace strategy {

template <typename Resource,
    typename std::enable_if<
    std::is_base_of<resource::Base, Resource>::value, bool>::type = true>
class Base
{
public:
  using resource_type = Resource;

  Base() : resource_{}, s_counter_{}, r_counter_{} {}
  virtual ~Base() {}
  Base(const Base& other) = delete;
  Base& operator=(const Base& other) = delete;

  void* allocate(std::size_t n)
  {
    s_counter_.allocate(n);
    return strategy_allocate(n);
  }

  void deallocate(void* p, std::size_t n)
  {
    s_counter_.deallocate(n);
    strategy_deallocate(p, n);
  }

  virtual void shrink_to_fit() = 0;

  void release()
  {
    s_counter_.size_ = 0;
    s_counter_.count_ = 0;
    strategy_release();
  }

  std::size_t strategy_size() const
  {
    return s_counter_.size_;
  }

  std::size_t strategy_size_max() const
  {
    return s_counter_.size_max_;
  }

  std::size_t strategy_count() const
  {
    return s_counter_.count_;
  }

  std::size_t resource_size() const
  {
    return r_counter_.size_;
  }

  std::size_t resource_size_max() const
  {
    return r_counter_.size_max_;
  }

  std::size_t resource_count() const
  {
    return r_counter_.count_;
  }

protected:
  virtual void* strategy_allocate(std::size_t n) = 0;

  virtual void strategy_deallocate(void* p, std::size_t n) = 0;

  virtual void strategy_release() = 0;

  void* resource_allocate(std::size_t n)
  {
    r_counter_.allocate(n);
    return resource_.allocate(n);
  }

  void resource_deallocate(void* p, std::size_t n)
  {
    r_counter_.deallocate(n);
    resource_.deallocate(p, n);
  }

private:
  struct Counter
  {
    Counter() : size_{ 0 }, size_max_{ 0 }, count_{ 0 } {}
    void allocate(std::size_t n)
    {
      size_ += n;
      if (size_max_ < size_) {
        size_max_ = size_;
      }
      ++count_;
    }
    void deallocate(std::size_t n)
    {
      size_ -= n;
      --count_;
    }
    std::size_t size_;
    std::size_t size_max_;
    std::size_t count_;
  };

  Resource resource_;
  Counter s_counter_;
  Counter r_counter_;
};

}
}

#endif // MEMO_STRATEGY_BASE_H
