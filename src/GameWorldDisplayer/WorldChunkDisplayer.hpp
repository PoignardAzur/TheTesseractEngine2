
#ifndef H_WORLD_AREA_DISPLAYER
#define H_WORLD_AREA_DISPLAYER

#include <Ogre.h>

#include <vector>
#include <map>

#include "GameWorld/WorldChunk.hpp"

constexpr size_t BLOCK_SIZE = 10;

class WorldChunkDisplayer
{
public:
  WorldChunkDisplayer(
    Ogre::SceneNode* rootNode,
    const std::map<BlockType, std::string>* blockTypes,
    const WorldChunk& chunk,
    Ogre::SceneManager* sceneManager
  );

  void setBlock(BPos pos, BlockType newBlock);
  void setBlock(long x, long y, long z, BlockType newBlock);

private:
  Ogre::SceneNode* m_rootNode;

  std::vector<Ogre::SceneNode*> m_blockNodes;
  BPos m_size;

  const std::map<BlockType, std::string>* m_blockTypes;

  Ogre::SceneManager* m_sceneManager;
};

#endif // !H_WORLD_AREA_DISPLAYER
