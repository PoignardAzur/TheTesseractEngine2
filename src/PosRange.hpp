
#ifndef H_POS_RANGE
#define H_POS_RANGE

#include <SFML/Graphics.hpp>

using BPos = sf::Vector3<long>;

// TODO: Unit tests

class PosRangeIt
{
public:
  PosRangeIt(BPos pos1, BPos pos2, long i);

  void operator++();
  bool operator!=(const PosRangeIt& other) const;
  BPos operator*() const;

private:
  BPos m_pos1;
  BPos m_size;
  long m_i;
};

class PosRange
{
public:
  PosRange(BPos pos1, BPos pos2);

  PosRangeIt begin() const;
  PosRangeIt end() const;

private:
  BPos m_pos1;
  BPos m_pos2;
  long m_volume;
};

#endif // !H_POS_RANGE
