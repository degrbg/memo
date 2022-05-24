#ifndef MEMO_STRATEGY_SLOTPOOL_H
#define MEMO_STRATEGY_SLOTPOOL_H

#include <vector>

#include <strategy/base.h>

namespace memo {
namespace strategy {

template <typename Resource>
class Slotpool : public Base<Resource>
{
public:
  Slotpool() {}

  ~Slotpool()
  {
    this->release();
  }

  void shrink_to_fit() override
  {
    std::vector<Slot> new_slots;
    for (const auto& slot : slots_) {
      if (slot.used_) {
        new_slots.emplace_back(slot);
      }
      else {
        this->resource_deallocate(slot.p_, slot.size_);
      }
    }
    slots_ = std::move(new_slots);
  }

protected:
  void* strategy_allocate(std::size_t n) override
  {
    void* p = nullptr;

    for (auto& slot : slots_) {
      if ((n == slot.size_) && !slot.used_) {
        slot.used_ = true;
        p = slot.p_;
        break;
      }
    }

    if (!p) {
      p = this->resource_allocate(n);
      slots_.emplace_back(n, true, p);
    }

    return p;
  }

  void strategy_deallocate(void* p, std::size_t n) override
  {
    for (auto& slot : slots_) {
      if (p == slot.p_) {
        slot.used_ = false;
        break;
      }
    }
  }

  void strategy_release() override
  {
    for (const auto& slot : slots_) {
      this->resource_deallocate(slot.p_, slot.size_);
    }
    slots_.clear();
    slots_.shrink_to_fit();
  }

private:
  struct Slot
  {
    Slot(std::size_t size, bool used, void* p) :
        size_{ size },
        used_{ used },
        p_{ p }
    {}
    const std::size_t size_;
    bool used_;
    void* const p_;
  };

  std::vector<Slot> slots_;
};

}
}

#endif // MEMO_STRATEGY_SLOTPOOL_H
