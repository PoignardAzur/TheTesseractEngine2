#ifndef H_SINGLE_CHUNK
#define H_SINGLE_CHUNK

#include "GameWorld.hpp"

class SingleChunk : public GameWorld
{
public:
  SingleChunk(WorldArea area);

  std::deque<Event> getUpdateEvents(Inputs::Rng& rng) const;
  void applyEvent(const Event& event);

  bool isAreaAvailable(BPos from, BPos to);
  Hitscan getHitscan(
    EPos pos, EOrient dir,
    float minDistance, float maxDistance, bool floatingBlock
  );

  std::deque<size_t> getChunkIds() const;
  const WorldArea& getChunk(size_t id) const;
  BPos getChunkPos(size_t id) const;

private:
  WorldArea m_area;
};

#endif // !H_SINGLE_CHUNK
