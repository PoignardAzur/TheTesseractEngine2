
#include <cassert>
#include "WorldChunk.hpp"

WorldChunk::WorldChunk(BPos size, BlockType fillBlock) :
  m_blockIds(size.x * size.y * size.z, fillBlock),
  m_size(size)
{

}

WorldChunk::WorldChunk(WorldChunk&& other) :
  m_blockIds(std::move(other.m_blockIds)),
  m_size(other.m_size)
{
  other.m_size = {0, 0, 0};
}

WorldChunk& WorldChunk::operator=(WorldChunk&& other)
{
  m_blockIds = std::move(other.m_blockIds);
  m_size = other.m_size;
  other.m_size = {0, 0, 0};

  return *this;
}

BlockType WorldChunk::getBlock(BPos pos) const
{
  return getBlock(pos.x, pos.y, pos.z);
}

BlockType WorldChunk::getBlock(long x, long y, long z) const
{
  assert(x >= 0 && y >= 0 && z >= 0);
  assert(x < m_size.x && y < m_size.y && z < m_size.z);
  return m_blockIds[x + y * m_size.y + z * m_size.z * m_size.z];
}

void WorldChunk::setBlock(BPos pos, BlockType newBlock)
{
  setBlock(pos.x, pos.y, pos.z, newBlock);
}

void WorldChunk::setBlock(long x, long y, long z, BlockType newBlock)
{
  assert(x >= 0 && y >= 0 && z >= 0);
  assert(x < m_size.x && y < m_size.y && z < m_size.z);
  m_blockIds[x + y * m_size.y + z * m_size.z * m_size.z] = newBlock;
}

BPos WorldChunk::getSize() const
{
  return m_size;
}

PosRange WorldChunk::getPosRange() const
{
  return PosRange({0, 0, 0}, { m_size.x, m_size.y, m_size.z});
}
