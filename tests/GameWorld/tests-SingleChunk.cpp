
#include "GameWorld/SingleChunk.hpp"

#include "../catch.hpp"
#include <iostream>
#include <deque>

static BPos pos0 = {0, 0, 0};

TEST_CASE("SingleChunk has one chunk", "[SingleChunk]")
{
  WorldChunk chunk({ 5, 5, 5 });
  int i = 0;
  for (BPos block : chunk.getPosRange())
  {
    if (i % 2)
      chunk.setBlock(block, BlockType::DIRT);
    i++;
  }

  SingleChunk worldChunk(chunk);

  SECTION("getChunkIds returns one value")
  {
    REQUIRE(worldChunk.getChunkIds() == std::deque<size_t>{ 0 });
  }

  SECTION("getChunk returns the given chunk")
  {
    const WorldChunk& chunk2 = worldChunk.getChunk(0);

    REQUIRE(chunk.getSize() == chunk2.getSize());
    for (BPos pos : chunk.getPosRange())
      REQUIRE(chunk.getBlock(pos) == chunk2.getBlock(pos));
  }

  SECTION("getChunkPos returns 0")
  {
    REQUIRE(worldChunk.getChunkPos(0) == pos0);
  }

  SECTION("available area is chunk size")
  {
    REQUIRE(worldChunk.isAreaAvailable(chunk.getPosRange()));
    REQUIRE(!worldChunk.isAreaAvailable(PosRange(pos0, {10, 10, 10})));
    REQUIRE(!worldChunk.isAreaAvailable(PosRange({1, 1, 1}, chunk.getSize())));
  }
}

TEST_CASE("SingleChunk - applyEvent", "[SingleChunk]")
{
  WorldChunk chunk({ 5, 5, 5 }, BlockType::STONE);
  SingleChunk world(std::move(chunk));

  SECTION("SetBlock")
  {
    world.applyEvent(GameWorld::Event{
      GameWorld::SetBlock,
      { 1, 1, 1 },
      { 1, 1, 1 },
      BlockType::DIRT
    });
    REQUIRE(world.getChunk(0).getBlock({1, 1, 1}) == BlockType::DIRT);
  }

  SECTION("RemoveBlock")
  {
    world.applyEvent(GameWorld::Event{
      GameWorld::RemoveBlock,
      { 1, 1, 1 },
      { 1, 1, 1 }
    });
    REQUIRE(world.getChunk(0).getBlock({1, 1, 1}) == BlockType::AIR);
  }

  SECTION("SetBlockRange")
  {
    world.applyEvent(GameWorld::Event{
      GameWorld::SetBlockRange,
      { 2, 2, 2 },
      { 3, 3, 3 },
      BlockType::DIRT
    });
    for (BPos pos : PosRange::betweenPos({ 2, 2, 2 }, { 3, 3, 3 }))
      REQUIRE(world.getChunk(0).getBlock(pos) == BlockType::DIRT);
  }

  SECTION("RemoveBlock")
  {
    world.applyEvent(GameWorld::Event{
      GameWorld::RemoveBlockRange,
      { 2, 2, 2 },
      { 3, 3, 3 }
    });
    for (BPos pos : PosRange::betweenPos({ 2, 2, 2 }, { 3, 3, 3 }))
      REQUIRE(world.getChunk(0).getBlock(pos) == BlockType::AIR);
  }
}

TEST_CASE("SingleChunk - getHitscan", "[SingleChunk]")
{
  // TODO
}
