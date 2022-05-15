#include <allocator/byte.h>

#include <resource/host.h>
#include <strategy/direct.h>

#include <gtest/gtest.h>


TEST(Byte, AllocateDeallocate)
{
  using Resource = memo::resource::Host;
  using Strategy = memo::strategy::Direct<Resource>;
  using Allocator = memo::allocator::Byte<Strategy>;

  constexpr int n = 1024;

  Allocator a;
  auto p = a.allocate(n);
  a.deallocate(p, n);
}
