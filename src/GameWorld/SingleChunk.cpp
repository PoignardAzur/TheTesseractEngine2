
#include <cassert>
#include "SingleChunk.hpp"

SingleChunk::SingleChunk(WorldArea area) :
  m_area(std::move(area))
{
}

// TODO
std::deque<SingleChunk::Event> SingleChunk::getUpdateEvents(Inputs::Rng& rng) const
{
  return {};
}

void SingleChunk::applyEvent(const SingleChunk::Event& event)
{

}

bool SingleChunk::isAreaAvailable(BPos from, BPos to)
{

}

GameWorld::Hitscan SingleChunk::getHitscan(
  EPos pos, EOrient dir,
  float minDistance, float maxDistance, bool floatingBlock
)
{

}

std::deque<size_t> SingleChunk::getChunkIds() const
{
  return { 0 };
}

const WorldArea& SingleChunk::getChunk(size_t id) const
{
  assert(id == 0);
  return m_area;
}

BPos SingleChunk::getChunkPos(size_t id) const
{
  assert(id == 0);
  return { 0, 0, 0 };
}
