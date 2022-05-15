#include <resource/host.h>

#include <gtest/gtest.h>


TEST(Host, AllocateDeallocate)
{
  memo::resource::Host host;

  constexpr int n = 1024;

  auto p = host.allocate(n);
  host.deallocate(p, n);
}
