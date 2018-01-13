
#include <cassert>
#include "GameWorld.hpp"

GameWorld::GameWorld()
{

}

GameWorld::GameWorld(WorldArea area) :
  m_chunkIds({ 0 })
{
  m_chunks[0] = { BPos(0, 0, 0), std::move(area) };
}

// TODO
std::deque<GameWorld::Event> GameWorld::getUpdateEvents(Inputs::Rng& rng) const
{
  return {};
}

// TODO
void GameWorld::applyEvent(const GameWorld::Event& event)
{
  (void)event;
}

std::deque<size_t> GameWorld::getChunkIds() const
{
  return m_chunkIds;
}

const WorldArea& GameWorld::getChunk(size_t id) const
{
  assert(m_chunks.count(id));
  return m_chunks.at(id).second;
}

BPos GameWorld::getChunkPos(size_t id) const
{
  assert(m_chunks.count(id));
  return m_chunks.at(id).first;
}
