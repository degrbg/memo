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
    for (auto& slot : slots_) {
      this->resource_deallocate(slot.p_, slot.size_);
    }
  }

  void shrink_to_fit() override
  {
    std::vector<Slot> new_slots;
    for (const auto& slot : slots_) {
      if (slot.used_) {
        new_slots.emplace_back(slot);
      }
      else if (slot.p_) {
        this->resource_deallocate(slot.p_, slot.size_);
      }
    }
    slots_ = std::move(new_slots);
  }

  void release() override
  {
    for (const auto& slot : slots_) {
      if (slot.p_) {
        this->resource_deallocate(slot.p_, slot.size_);
      }
    }
    slots_.clear();
    slots_.shrink_to_fit();
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

      Slot new_slot{ n, true, p };
      bool found_empty_slot = false;

      for (auto& slot : slots_) {
        if (slot.p_ == nullptr) {
          slot = new_slot;
          found_empty_slot = true;
          break;
        }
      }

      if (!found_empty_slot) {
        slots_.emplace_back(new_slot);
      }
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

private:
  struct Slot
  {
    std::size_t size_;
    bool used_;
    void* p_;
  };

  std::vector<Slot> slots_;
};

}
}

#endif // MEMO_STRATEGY_SLOTPOOL_H
