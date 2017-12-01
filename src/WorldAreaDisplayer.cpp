
#include "WorldAreaDisplayer.hpp"

#include <OgreEntity.h>

WorldAreaDisplayer::WorldAreaDisplayer(
  Ogre::SceneNode* rootNode,
  const std::map<BlockType, std::string>* blockTypes,
  const WorldArea& area,
  Ogre::SceneManager* sceneManager
)
{
  m_rootNode = rootNode;
  m_size = area.getSize();
  m_blockNodes.resize(m_size.x * m_size.y * m_size.z);

  for (BPos pos: area.getPosRange())
  {
    setBlock(pos, area.getBlock(pos));
  }

  m_blockTypes = blockTypes;
  m_sceneManager = sceneManager;
}

void WorldAreaDisplayer::setBlock(BPos pos, BlockType newBlock)
{
  setBlock(pos.x, pos.y, pos.z, newBlock);
}

void WorldAreaDisplayer::setBlock(long x, long y, long z, BlockType newBlock)
{
  assert(x < m_size.x && y < m_size.y && z < m_size.z);
  assert(m_blockTypes->count(newBlock));

  long i = x + y * m_size.y + z * m_size.z * m_size.z;

  if (m_blockNodes[i] != BlockType::AIR)
    m_chunkNode->removeChild(blockNode);

  if (newBlock != BlockType::AIR)
  {
    Ogre::Entity *blockEntity = m_sceneManager->createEntity("Cube_mesh");
    blockEntity->setMaterialName((*m_blockTypes)[newBlock]);

    m_blockNodes[i] = m_chunkNode->createChildSceneNode(
      Ogre::Vector3(x * BLOCK_SIZE, y * BLOCK_SIZE, z * BLOCK_SIZE)
    );
    m_blockNodes[i]->setScale(10, 10, 10);
    m_blockNodes[i]->attachObject(blockEntity);
  }
}
