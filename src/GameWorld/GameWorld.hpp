
#ifndef H_GAME_WORLD
#define H_GAME_WORLD

#include <deque>
#include <memory>
#include <optional>

#include "Inputs/Inputs.hpp"
#include "WorldChunk.hpp"

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
    BPos blockPos2;
    BlockType blockType;
  };

  struct Hitscan
  {
    std::optional<BPos> blockTarget_break;
    std::optional<BPos> blockTarget_place;
    // Entity* entityTarget = nullptr;
  };

  struct AreaSlice
  {
    PosRange posRange;
    size_t chunkId;
  };

  using Ptr = std::unique_ptr<GameWorld>;

  virtual std::deque<Event> getUpdateEvents(Inputs::Rng& rng) const = 0;
  virtual void applyEvent(const Event& event) = 0;

  virtual bool isAreaAvailable(const PosRange& area) const = 0;
  virtual std::deque<AreaSlice> sliceArea(const PosRange& area) const = 0;
  virtual Hitscan getHitscan(
    EPos pos, EOrient dir,
    float minDistance, float maxDistance, bool floatingBlock
  ) const = 0;

  virtual std::deque<size_t> getChunkIds() const = 0;
  virtual const WorldChunk& getChunk(size_t id) const = 0;
  virtual BPos getChunkPos(size_t id) const = 0;

  // TODO - save
  // TODO - load
};

#endif // !H_GAME_WORLD
