
#include <OgreEntity.h>
#include <cassert>

#include "WorldAreaDisplayer.hpp"

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

  m_blockTypes = blockTypes;
  m_sceneManager = sceneManager;

  for (BPos pos: area.getPosRange())
  {
    setBlock(pos, area.getBlock(pos));
  }
}

void WorldAreaDisplayer::setBlock(BPos pos, BlockType newBlock)
{
  setBlock(pos.x, pos.y, pos.z, newBlock);
}

void WorldAreaDisplayer::setBlock(long x, long y, long z, BlockType newBlock)
{
  assert(x >= 0 && y >= 0 && z >= 0);
  assert(x < m_size.x && y < m_size.y && z < m_size.z);
  assert(newBlock == BlockType::AIR || m_blockTypes->count(newBlock));

  long i = x + y * m_size.y + z * m_size.z * m_size.z;

  if (m_blockNodes[i] != nullptr)
    m_rootNode->removeChild(m_blockNodes[i]);

  if (newBlock != BlockType::AIR)
  {
    Ogre::Entity *blockEntity = m_sceneManager->createEntity("Cube_mesh");
    blockEntity->setMaterialName(m_blockTypes->at(newBlock));

    m_blockNodes[i] = m_rootNode->createChildSceneNode(
      Ogre::Vector3(x * BLOCK_SIZE, y * BLOCK_SIZE, z * BLOCK_SIZE)
    );
    m_blockNodes[i]->setScale(10, 10, 10);
    m_blockNodes[i]->attachObject(blockEntity);
  }
}
