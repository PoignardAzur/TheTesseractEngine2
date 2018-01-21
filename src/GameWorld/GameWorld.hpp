
#ifndef H_GAME_WORLD
#define H_GAME_WORLD

#include <deque>
#include <memory>

#include "Inputs/Inputs.hpp"
#include "WorldArea.hpp"

#include "EntityPos.hpp"
#include "EntityOrientation.hpp"

class GameWorld
{
public:
  enum EventType
  {
    SetBlock, RemoveBlock,
    SetBlockRange, RemoveBlockRange,
    EventCount
  };

  struct Event
  {
    EventType type;
    BPos blockPos;
    BlockType blockType;
  };

  struct Hitscan
  {

  };

  using Ptr = std::unique_ptr<GameWorld>;

  virtual std::deque<Event> getUpdateEvents(Inputs::Rng& rng) const = 0;
  virtual void applyEvent(const Event& event) = 0;

  virtual bool isAreaAvailable(BPos from, BPos to) = 0;
  virtual Hitscan getHitscan(
    EPos pos, EOrient dir,
    float minDistance, float maxDistance, bool floatingBlock
  ) = 0;

  virtual std::deque<size_t> getChunkIds() const = 0;
  virtual const WorldArea& getChunk(size_t id) const = 0;
  virtual BPos getChunkPos(size_t id) const = 0;

  // TODO - save
  // TODO - load
};

#endif // !H_GAME_WORLD
