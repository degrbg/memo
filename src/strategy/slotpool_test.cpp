#include <strategy/slotpool.h>

#include <resource/host.h>

#include <gtest/gtest.h>


using Resource = memo::resource::Host;
using Strategy = memo::strategy::Slotpool<Resource>;


void check_counter(const Strategy& s,
    std::size_t ss, std::size_t ssm, std::size_t sc,
    std::size_t rs, std::size_t rsm, std::size_t rc)
{
  EXPECT_EQ(s.strategy_size(),     ss );
  EXPECT_EQ(s.strategy_size_max(), ssm);
  EXPECT_EQ(s.strategy_count(),    sc );

  EXPECT_EQ(s.resource_size(),     rs );
  EXPECT_EQ(s.resource_size_max(), rsm);
  EXPECT_EQ(s.resource_count(),    rc );
}


TEST(Slotpool, AllocateDeallocate)
{
  constexpr int n = 1024;
  Strategy s;

  auto p = s.allocate(n);
  check_counter(s, n, n, 1, n, n, 1);

  s.deallocate(p, n);
  check_counter(s, 0, n, 0, n, n, 1);
}


TEST(Slotpool, ShrinkToFit)
{
  constexpr int n = 1024;
  Strategy s;

  auto p = s.allocate(n);
  check_counter(s, n, n, 1, n, n, 1);

  s.shrink_to_fit();
  check_counter(s, n, n, 1, n, n, 1);

  s.deallocate(p, n);
  check_counter(s, 0, n, 0, n, n, 1);

  s.shrink_to_fit();
  check_counter(s, 0, n, 0, 0, n, 0);
}


TEST(Slotpool, Release)
{
  constexpr int n = 1024;
  Strategy s;

  auto p = s.allocate(n);
  check_counter(s, n, n, 1, n, n, 1);

  s.release();
  check_counter(s, 0, n, 0, 0, n, 0);
}
