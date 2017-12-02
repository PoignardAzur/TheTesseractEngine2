
#ifndef H_GAME_WORLD
#define H_GAME_WORLD

#include <deque>
#include <map>
#include <memory>

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
  GameWorld(WorldArea area);

  std::deque<Event> getUpdateEvents(Inputs::Rng& rng) const;

  void applyEvent(const Event& event);

  std::deque<size_t> getChunkIds() const;
  const WorldArea& getChunk(size_t id) const;
  BPos getChunkPos(size_t id) const;

  // TODO - save
  // TODO - load

  using Ptr = std::unique_ptr<GameWorld>;

private:
  std::deque<size_t> m_chunkIds;
  std::map<size_t, std::pair<BPos, WorldArea>> m_chunks;
};

#endif // !H_GAME_WORLD
