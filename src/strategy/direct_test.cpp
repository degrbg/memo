#include <strategy/direct.h>

#include <resource/host.h>

#include <gtest/gtest.h>


using Resource = memo::resource::Host;
using Strategy = memo::strategy::Direct<Resource>;


TEST(Direct, AllocateDeallocate)
{
  constexpr int n = 1024;
  Strategy s;

  auto p = s.allocate(n);
  s.deallocate(p, n);
}


TEST(Direct, ShrinkToFit)
{
  Strategy s;

  // No-op
  s.shrink_to_fit();
}


TEST(Direct, Release)
{
  Strategy s;

  // No-op
  s.release();
}
