#ifndef H_SINGLE_CHUNK
#define H_SINGLE_CHUNK

#include "GameWorld.hpp"

class SingleChunk : public GameWorld
{
public:
  SingleChunk(WorldChunk chunk);

  std::deque<Event> getUpdateEvents(Inputs::Rng& rng) const;
  void applyEvent(const Event& event);

  bool isAreaAvailable(const PosRange& area) const;
  std::deque<AreaSlice> sliceArea(const PosRange& area) const;
  Hitscan getHitscan(
    EPos pos, EOrient dir,
    float minDistance, float maxDistance, bool floatingBlock
  ) const;

  std::deque<size_t> getChunkIds() const;
  const WorldChunk& getChunk(size_t id) const;
  BPos getChunkPos(size_t id) const;

private:
  WorldChunk m_chunk;
};

#endif // !H_SINGLE_CHUNK
