
#include <cassert>
#include "PosRange.hpp"

PosRangeIt::PosRangeIt(BPos minPos, BPos size, long i) :
  m_minPos(minPos),
  m_size(size),
  m_i(i)
{

}

void PosRangeIt::operator++()
{
  ++m_i;
}

bool PosRangeIt::operator!=(const PosRangeIt& other) const
{
  assert(m_minPos == other.m_minPos);
  assert(m_size == other.m_size);
  return m_i != other.m_i;
}

BPos PosRangeIt::operator*() const
{
  return {
    m_minPos.x + m_i % m_size.x,
    m_minPos.y + (m_i / m_size.x) % m_size.y,
    m_minPos.z + (m_i / m_size.x) / m_size.y,
  };
}

PosRange::PosRange(BPos minPos, BPos size) :
  minPos(minPos),
  size(size)
{
  assert(size.x >= 0);
  assert(size.y >= 0);
  assert(size.z >= 0);
}

PosRange PosRange::betweenPos(BPos pos1, BPos pos2)
{
  BPos minPos(
    std::min(pos1.x, pos2.x),
    std::min(pos1.y, pos2.y),
    std::min(pos1.z, pos2.z)
  );
  BPos maxPos(
    std::max(pos1.x, pos2.x),
    std::max(pos1.y, pos2.y),
    std::max(pos1.z, pos2.z)
  );
  BPos size(
    maxPos.x - minPos.x + 1,
    maxPos.y - minPos.y + 1,
    maxPos.z - minPos.z + 1
  );

  return PosRange(minPos, size);
}

bool PosRange::contains(BPos pos) const
{
  return (
    pos.x >= minPos.x && pos.x < minPos.x + size.x &&
    pos.y >= minPos.y && pos.y < minPos.y + size.y &&
    pos.z >= minPos.z && pos.z < minPos.z + size.z
  );
}

bool PosRange::contains(EPos pos) const
{
  return (
    pos.x >= minPos.x && pos.x < minPos.x + size.x &&
    pos.y >= minPos.y && pos.y < minPos.y + size.y &&
    pos.z >= minPos.z && pos.z < minPos.z + size.z
  );
}

bool PosRange::contains(const PosRange& other) const
{
  return (
    other.minPos.x >= minPos.x &&
    other.minPos.x + other.size.x <= minPos.x + size.x &&
    other.minPos.y >= minPos.y &&
    other.minPos.y + other.size.y <= minPos.y + size.y &&
    other.minPos.z >= minPos.z &&
    other.minPos.z + other.size.z <= minPos.z + size.z
  );
}

bool PosRange::operator==(const PosRange& other) const
{
  return minPos == other.minPos && size == other.size;
}

bool PosRange::operator!=(const PosRange& other) const
{
  return !(minPos == other.minPos && size == other.size);
}

PosRangeIt PosRange::begin() const
{
  return PosRangeIt(minPos, size, 0);
}

PosRangeIt PosRange::end() const
{
  return PosRangeIt(minPos, size, size.x * size.y * size.z);
}

std::ostream& operator<<(std::ostream& os, const BPos& pos)
{
	os << "BPos(" << pos.x << ", " << pos.y << ", " << pos.z << ")";
	return os;
}

std::ostream& operator<<(std::ostream& os, const PosRange& rg)
{
	os << "PosRange(minPos: " << rg.minPos << ", size: " << rg.size << ")";
	return os;
}
