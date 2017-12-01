
#include <cassert>
#include "GameWorld.hpp"

GameWorld::GameWorld()
{

}

GameWorld::GameWorld(const WorldArea& area) :
  m_chunkIds({ 0 })
{
  m_chunks[0] = { {0, 0, 0}, area };
}

// TODO
std::deque<Event> GameWorld::getUpdateEvents(Inputs::Rng& rng) const
{
  return {};
}

// TODO
void GameWorld::applyEvent(const Event& event);
{
  (void)event;
}

std::deque<size_t> GameWorld::getChunkIds()
{
  return m_chunkIds;
}

const WorldArea& GameWorld::getChunk(size_t id)
{
  assert(m_chunks.count(id));
  return m_chunks[id].first;
}

BPos GameWorld::getChunkPos(id)
{
  assert(m_chunks.count(id));
  return m_chunks[id].second;
}
