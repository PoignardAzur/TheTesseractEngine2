
#include <cassert>
#include "PosRange.hpp"

PosRangeIt::PosRangeIt(BPos pos1, BPos pos2, long i) :
  m_pos1(pos1),
  m_size(pos2 - pos1),
  m_i(i)
{

}

void PosRangeIt::operator++()
{
  ++m_i;
}

bool PosRangeIt::operator!=(const PosRangeIt& other) const
{
  assert(m_pos1 == other.m_pos1);
  assert(m_size == other.m_size);
  return m_i != other.m_i;
}

BPos PosRangeIt::operator*() const
{
  return {
    m_pos1.x + m_i % m_size.x,
    m_pos1.y + (m_i / m_size.x) % m_size.y,
    m_pos1.z + (m_i / m_size.x) / m_size.y,
  };
}

PosRange::PosRange(BPos pos1, BPos pos2) :
  m_pos1(pos1),
  m_pos2(pos2)
{
  m_volume = (pos2.x - pos1.x) * (pos2.y - pos1.y) * (pos2.z - pos1.z);
}

PosRangeIt PosRange::begin() const
{
  return PosRangeIt(m_pos1, m_pos2, 0);
}

PosRangeIt PosRange::end() const
{
  return PosRangeIt(m_pos1, m_pos2, m_volume);
}
