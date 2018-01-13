
#ifndef H_WORLD_CHUNK
#define H_WORLD_CHUNK

#include <memory>
#include <vector>

#include "BlockType.hpp"
#include "BlockPos.hpp"
#include "PosRange.hpp"

constexpr long CHUNK_SIZE = 16;

class WorldArea
{
public:
  WorldArea(
    BPos size = { CHUNK_SIZE, CHUNK_SIZE, CHUNK_SIZE },
    BlockType fillBlock = BlockType::AIR
  );
  WorldArea(const WorldArea& other) = default;
  WorldArea(WorldArea&& other) = default;
  WorldArea& operator=(const WorldArea& other) = default;
  WorldArea& operator=(WorldArea&& other) = default;

  BlockType getBlock(BPos pos) const;
  BlockType getBlock(long x, long y, long z) const;
  void setBlock(BPos pos, BlockType newBlock);
  void setBlock(long x, long y, long z, BlockType newBlock);

  BPos getSize() const;
  PosRange getPosRange() const;

  using Ptr = std::unique_ptr<WorldArea>;

private:
  std::vector<BlockType> m_blockIds;
  BPos m_size;
};

#endif // !H_WORLD_CHUNK
