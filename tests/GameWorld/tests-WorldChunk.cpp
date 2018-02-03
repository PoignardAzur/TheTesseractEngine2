
#include "GameWorld/WorldChunk.hpp"

#include "../catch.hpp"
#include <iostream>
#include <deque>

static BPos pos0 = {0, 0, 0};

TEST_CASE("WorldChunk constructor", "[WorldChunk]")
{
  std::deque<BPos> sizes = {
    pos0,
    { 0, 5, 5 },
    { 5, 0, 5 },
    { 5, 5, 0 },
    { 5, 0, 0 },
    { 0, 5, 0 },
    { 0, 0, 5 },

    { 5, 5, 5 }
  };

  SECTION("respects size")
  {
    for (BPos size : sizes)
    {
      REQUIRE(WorldChunk(size).getSize() == size);
      REQUIRE(WorldChunk(size).getPosRange() == PosRange(pos0, size));
    }
  }


  SECTION("fills with blocks")
  {
    for (BPos size : sizes)
    {
      WorldChunk airChunk(size);

      for (BPos block : airChunk.getPosRange())
      {
        REQUIRE(airChunk.getBlock(block) == BlockType::AIR);
      }

      WorldChunk dirtChunk(size, BlockType::DIRT);

      for (BPos block : dirtChunk.getPosRange())
      {
        REQUIRE(dirtChunk.getBlock(block) == BlockType::DIRT);
      }
    }
  }

}

TEST_CASE("WorldChunk can get and set blocks", "[WorldChunk]")
{
  auto testChunk = [](const WorldChunk& testedChunk)
  {
    int i = 0;
    for (BPos block : testedChunk.getPosRange())
    {
      REQUIRE(
        testedChunk.getBlock(block) ==
        (i % 2 ? BlockType::DIRT : BlockType::AIR)
      );
      i++;
    }
  };

  WorldChunk chunk({ 5, 5, 5 });
  int i = 0;
  for (BPos block : chunk.getPosRange())
  {
    if (i % 2)
      chunk.setBlock(block, BlockType::DIRT);
    i++;
  }

  SECTION("get blocks")
  {
    testChunk(chunk);
  }

  SECTION("chunk copy")
  {
    SECTION("copy constructor")
    {
      WorldChunk chunk2 = chunk;
      testChunk(chunk2);
    }

    SECTION("copy assignment")
    {
      WorldChunk chunk2;
      chunk2 = chunk;
      testChunk(chunk2);
    }

    SECTION("move constructor")
    {
      WorldChunk chunk2 = std::move(chunk);
      testChunk(chunk2);
      REQUIRE(chunk.getSize() == pos0);
    }

    SECTION("move assignment")
    {
      WorldChunk chunk2;
      chunk2 = std::move(chunk);
      testChunk(chunk2);
      REQUIRE(chunk.getSize() == pos0);
    }
  }
}
