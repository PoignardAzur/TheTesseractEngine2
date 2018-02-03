
#ifndef H_POS_RANGE
#define H_POS_RANGE

#include "BlockPos.hpp"
#include "EntityPos.hpp"

class PosRangeIt
{
public:
  PosRangeIt(BPos minPos, BPos size, long i);

  void operator++();
  bool operator!=(const PosRangeIt& other) const;
  BPos operator*() const;

private:
  BPos m_minPos;
  BPos m_size;
  long m_i;
};

struct PosRange
{
public:
  PosRange(BPos minPos, BPos size);
  static PosRange betweenPos(BPos pos1, BPos pos2);

  const BPos minPos;
  const BPos size;

  bool contains(BPos pos) const;
  bool contains(EPos pos) const;
  bool contains(const PosRange& other) const;

  bool operator==(const PosRange& other) const;
  bool operator!=(const PosRange& other) const;

  PosRangeIt begin() const;
  PosRangeIt end() const;
};

std::ostream& operator<<(std::ostream& os, const BPos& pos);
std::ostream& operator<<(std::ostream& os, const PosRange& rg);

#endif // !H_POS_RANGE
