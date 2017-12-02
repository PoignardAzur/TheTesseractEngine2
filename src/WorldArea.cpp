
#include <cassert>
#include "WorldArea.hpp"

WorldArea::WorldArea(BPos size, BlockType fillBlock) :
  m_blockIds(size.x * size.y * size.z, fillBlock),
  m_size(size)
{

}

BlockType WorldArea::getBlock(BPos pos) const
{
  return getBlock(pos.x, pos.y, pos.z);
}

BlockType WorldArea::getBlock(long x, long y, long z) const
{
  assert(x >= 0 && y >= 0 && z >= 0);
  assert(x < m_size.x && y < m_size.y && z < m_size.z);
  return m_blockIds[x + y * m_size.y + z * m_size.z * m_size.z];
}

void WorldArea::setBlock(BPos pos, BlockType newBlock)
{
  setBlock(pos.x, pos.y, pos.z, newBlock);
}

void WorldArea::setBlock(long x, long y, long z, BlockType newBlock)
{
  assert(x >= 0 && y >= 0 && z >= 0);
  assert(x < m_size.x && y < m_size.y && z < m_size.z);
  m_blockIds[x + y * m_size.y + z * m_size.z * m_size.z] = newBlock;
}

BPos WorldArea::getSize() const
{
  return m_size;
}

PosRange WorldArea::getPosRange() const
{
  return PosRange({0, 0, 0}, m_size);
}
