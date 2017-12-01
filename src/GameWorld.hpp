
#ifndef H_GAME_WORLD
#define H_GAME_WORLD

#include <deque>
#include <map>

#include "Inputs.hpp"
#include "WorldArea.hpp"

class GameWorld
{
public:
  enum EventType
  {
    AddBlock, RemoveBlock, ReplaceBlock,
    AddBlockRange, RemoveBlockRange, ReplaceBlockRange,
    EventCount
  };

  struct Event
  {
    EventType type;
    BPos blockPos;
  };

  GameWorld();
  GameWorld(const WorldArea& area);

  std::deque<Event> getUpdateEvents(Inputs::Rng& rng) const;

  void applyEvent(const Event& event);

  std::deque<size_t> getChunkIds();
  const WorldArea& getChunk(size_t id);
  BPos getChunkPos(size_t id);

  // TODO - save
  // TODO - load

private:
  std::deque<size_t> m_chunkIds;
  std::map<size_t, std::pair<BPos, WorldArea>> m_chunks;
};

#endif // !H_GAME_WORLD
