
#include <cmath>
#include <cassert>
#include "SingleChunk.hpp"

SingleChunk::SingleChunk(WorldChunk chunk) :
  m_chunk(std::move(chunk))
{
}

// TODO
std::deque<GameWorld::Event> SingleChunk::getUpdateEvents(Inputs::Rng& rng) const
{
  return {};
}

static PosRange _getRange(const GameWorld::Event& event)
{
  switch (event.type)
  {
    case GameWorld::SetBlock:
    case GameWorld::RemoveBlock:
      return PosRange::betweenPos(event.blockPos, event.blockPos);
    break;

    case GameWorld::SetBlockRange:
    case GameWorld::RemoveBlockRange:
      return PosRange::betweenPos(event.blockPos, event.blockPos2);
    break;

    case GameWorld::EventCount:
    break;
  }
  assert(false);
}

void SingleChunk::applyEvent(const GameWorld::Event& event)
{
  assert(isAreaAvailable(_getRange(event)));

  switch (event.type)
  {
    case SetBlock:
      m_chunk.setBlock(event.blockPos, event.blockType);
    break;

    case RemoveBlock:
      m_chunk.setBlock(event.blockPos, BlockType::AIR);
    break;

    case SetBlockRange:
      for (BPos pos : PosRange(event.blockPos, event.blockPos2))
        m_chunk.setBlock(pos, event.blockType);
    break;

    case RemoveBlockRange:
      for (BPos pos : PosRange(event.blockPos, event.blockPos2))
        m_chunk.setBlock(pos, BlockType::AIR);
    break;

    case EventCount:
      assert(false);
    break;
  }
}

bool SingleChunk::isAreaAvailable(const PosRange& area) const
{
  return m_chunk.getPosRange().contains(area);
}

auto SingleChunk::sliceArea(const PosRange& area) const
  -> std::deque<AreaSlice>
{
  assert(isAreaAvailable(area));
  return { { area, 0 } };
}

EPos _getBlockOf(EPos pos)
{
  using std::floor;
  return { floor(pos.x), floor(pos.y), floor(pos.z) };
}

// returns a pointer to structure member
auto _nextPlanCrossed(EPos dist_untilNextPlan)
{
  auto dist = dist_untilNextPlan;

  if (dist.x < dist.y && dist.x < dist.z)
    return &EPos::x;
  else if (dist.y < dist.z)
    return &EPos::y;
  else
    return &EPos::z;
}

float _untilNextInt(float value, float coeff)
{
  // if coeff < 0 || coeff == -0
  if (std::signbit(coeff))
    return _untilNextInt(-value, -coeff);

  // solve x for value + x * coeff = floor(value) + 1
  else
    return (std::floor(value) + 1.0f - value) / coeff;
}

BPos _toBPos(EPos p)
{
  return { (long)p.x, (long)p.y, (long)p.z };
}

GameWorld::Hitscan SingleChunk::getHitscan(
  EPos pos, EOrient dir,
  float minDistance, float maxDistance, bool floatingBlock
) const
{
  Ogre::Vector3 dirVec_ = dir * -Ogre::Vector3::UNIT_Z;
  EPos dirVec = { dirVec_.x, dirVec_.y, dirVec_.z};

  EPos blockIncrement = {
    std::signbit(dirVec.x) ? -1.0f : 1.0f,
    std::signbit(dirVec.y) ? -1.0f : 1.0f,
    std::signbit(dirVec.z) ? -1.0f : 1.0f
  };
  EPos dist_untilNextPlan = {
    _untilNextInt(pos.x, dirVec.x),
    _untilNextInt(pos.y, dirVec.y),
    _untilNextInt(pos.z, dirVec.z)
  };
  EPos dist_betweenPlans = {
    blockIncrement.x / dirVec.x,
    blockIncrement.y / dirVec.y,
    blockIncrement.z / dirVec.z
  };

  EPos targetBlock = _getBlockOf(pos);
  std::optional<EPos> previousBlock;

  float dist = 0.f;

  while (!m_chunk.getPosRange().contains(targetBlock) && dist < maxDistance)
  {
    auto xyz = _nextPlanCrossed(dist_untilNextPlan);

    // foobar.*xyz is equivalent to either foobar.x, foobar.y or foobar.z
    dist = dist_untilNextPlan.*xyz;
    dist_untilNextPlan.*xyz += dist_betweenPlans.*xyz;

    targetBlock.*xyz += blockIncrement.*xyz;
  }
  while (m_chunk.getPosRange().contains(targetBlock) && dist < maxDistance)
  {
    if (m_chunk.getBlock(_toBPos(targetBlock)) != BlockType::AIR)
    {
      if (dist < minDistance)
        return {};

      Hitscan hitscan;
      hitscan.blockTarget_break = _toBPos(targetBlock);
      if (previousBlock)
        hitscan.blockTarget_place = _toBPos(*previousBlock);
      return hitscan;
    }

    auto xyz = _nextPlanCrossed(dist_untilNextPlan);

    dist = dist_untilNextPlan.*xyz;
    dist_untilNextPlan.*xyz += dist_betweenPlans.*xyz;

    previousBlock = targetBlock;
    targetBlock.*xyz += blockIncrement.*xyz;
  }
  return {};
}

std::deque<size_t> SingleChunk::getChunkIds() const
{
  return { 0 };
}

const WorldChunk& SingleChunk::getChunk(size_t id) const
{
  assert(id == 0);
  return m_chunk;
}

BPos SingleChunk::getChunkPos(size_t id) const
{
  assert(id == 0);
  return { 0, 0, 0 };
}
