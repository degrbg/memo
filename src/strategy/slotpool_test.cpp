#include <strategy/slotpool.h>

#include <resource/host.h>

#include <gtest/gtest.h>


TEST(Slotpool, AllocateDeallocate)
{
  using Resource = memo::resource::Host;
  using Strategy = memo::strategy::Slotpool<Resource>;

  constexpr int n = 1024;

  Strategy s;
  auto p = s.allocate(n);
  s.deallocate(p, n);
}
