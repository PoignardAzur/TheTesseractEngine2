
#include "GameWorld/PosRange.hpp"

#include "../catch.hpp"
#include <iostream>
#include <deque>


TEST_CASE("betweenPos sorts its values at construction", "[PosRange]")
{
  auto compare = [](BPos pos1, BPos pos2)
  {
    PosRange range1 = PosRange::betweenPos(pos1, pos2);
    PosRange range2 = PosRange::betweenPos(pos2, pos1);

    REQUIRE(range1 == range2);
  };

  compare({0, 0, 0}, {1, 1, 1});
  compare({-1, -1, -1}, {0, 0, 0});
  compare({10, 10, 0}, {-100, 100, -100});
  compare({1, 2, 3}, {3, 2, 1});
}

std::deque<BPos> _getValues(const PosRange& range)
{
  std::deque<BPos> values;

  for (BPos pos: range)
  {
    values.push_back(pos);
  }
  return values;
};

const std::deque<PosRange> emptyRanges = {
  PosRange({0, 0, 0}, {0, 0, 0}),

  PosRange({0, 0, 0}, {10, 0, 0}),
  PosRange({0, 0, 0}, {0, 10, 0}),
  PosRange({0, 0, 0}, {0, 0, 10}),

  PosRange({0, 0, 0}, {0, 10, 10}),
  PosRange({0, 0, 0}, {10, 0, 10}),
  PosRange({0, 0, 0}, {10, 10, 0}),
};

TEST_CASE("PosRange can be iterated through", "[PosRange]")
{
  SECTION("empty or flat ranges don't iterate")
  {
    for (PosRange range : emptyRanges)
    {
      REQUIRE(_getValues(range).size() == 0);
    }
  }

  SECTION("values are iterated by x, then y, then z")
  {
    PosRange smallRange({42, 42, 42}, {1, 1, 1});
    PosRange biggerRange({42, 42, 42}, {2, 2, 2});

    REQUIRE(
      _getValues(smallRange) ==
      std::deque<BPos>{ {42, 42, 42} }
    );

    REQUIRE(
      _getValues(biggerRange) ==
      std::deque<BPos>{
        {42, 42, 42},
        {43, 42, 42},
        {42, 43, 42},
        {43, 43, 42},

        {42, 42, 43},
        {43, 42, 43},
        {42, 43, 43},
        {43, 43, 43},
      }
    );
  }
}

TEST_CASE("PosRange can test collisions", "[PosRange]")
{
  PosRange emptyRange({0, 0, 0}, {0, 0, 0});
  PosRange bigRange({42, 42, 42}, {8, 8, 8});

  SECTION("empty or flat ranges contain nothing")
  {
    EPos pos0 = {0, 0, 0};

    PosRange flatRange1({0, 0, 0}, {10, 0, 0});
    PosRange flatRange2({0, 0, 0}, {0, 10, 0});
    PosRange flatRange3({0, 0, 0}, {0, 0, 10});

    PosRange flatRange4({0, 0, 0}, {0, 10, 10});
    PosRange flatRange5({0, 0, 0}, {10, 0, 10});
    PosRange flatRange6({0, 0, 0}, {10, 10, 0});

    REQUIRE(!emptyRange.contains(pos0));
    REQUIRE(!flatRange1.contains(pos0));
    REQUIRE(!flatRange2.contains(pos0));
    REQUIRE(!flatRange3.contains(pos0));
    REQUIRE(!flatRange4.contains(pos0));
    REQUIRE(!flatRange5.contains(pos0));
    REQUIRE(!flatRange6.contains(pos0));
  }

  SECTION("ranges contain all their values")
  {
    for (BPos pos : bigRange)
    {
      REQUIRE(bigRange.contains(pos));
      REQUIRE(bigRange.contains(EPos{
        pos.x + 0.5f,
        pos.y + 0.5f,
        pos.z + 0.5f
      }));
      REQUIRE(bigRange.contains(PosRange(
        pos,
        BPos(
          bigRange.size.x - (pos.x - bigRange.minPos.x),
          bigRange.size.y - (pos.y - bigRange.minPos.y),
          bigRange.size.z - (pos.z - bigRange.minPos.z)
        )
      )));
    }
  }

  SECTION("ranges don't contain outside points")
  {
    std::deque<BPos> values = {
      BPos{-1, -1, -1},
      BPos{100, 100, 100},
      BPos{41, 41, 41},
      BPos{41, 42, 42},
      BPos{42, 41, 42},
      BPos{42, 42, 41},
      BPos{50, 50, 50},
      BPos{50, 42, 42},
      BPos{42, 50, 42},
      BPos{42, 42, 50}
    };

    for (BPos pos : values)
    {
      REQUIRE(!bigRange.contains(pos));
      REQUIRE(!bigRange.contains(EPos{
        pos.x + 0.5f,
        pos.y + 0.5f,
        pos.z + 0.5f
      }));
      REQUIRE(!bigRange.contains(PosRange(pos, {1, 1, 1})));
    }
  }

  SECTION("ranges contain themselves")
  {
    REQUIRE(emptyRange.contains(emptyRange));
    REQUIRE(bigRange.contains(bigRange));
  }

  SECTION("ranges don't contain outside ranges")
  {
    std::deque<PosRange> values = {
      emptyRange,
      PosRange({42, 42, 42}, {9, 9, 9}),

      PosRange({43, 42, 42}, {8, 8, 8}),
      PosRange({42, 43, 42}, {8, 8, 8}),
      PosRange({42, 42, 43}, {8, 8, 8}),

      PosRange({41, 42, 42}, {8, 8, 8}),
      PosRange({42, 41, 42}, {8, 8, 8}),
      PosRange({42, 42, 41}, {8, 8, 8}),
    };

    for (PosRange range : values)
    {
      REQUIRE(!bigRange.contains(range));
    }
  }
}
