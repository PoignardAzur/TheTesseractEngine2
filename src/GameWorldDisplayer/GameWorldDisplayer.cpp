
#include <cassert>
#include "GameWorldDisplayer.hpp"

GameWorldDisplayer::GameWorldDisplayer(const GameWorld* world)
{
  m_world = world;

  m_sceneManager = new Ogre::DefaultSceneManager("Scene0");
  m_sceneManager->createCamera("cam");
  m_sceneManager->setAmbientLight(Ogre::ColourValue(1, 1, 1));

  m_blockTypes = {
    { BlockType::STONE, "Cube/Stone" },
    { BlockType::DIRT, "Cube/Dirt" }
  };

  m_chunkIds = m_world->getChunkIds();
  for (size_t id : m_chunkIds)
  {
    float chunkSize = CHUNK_SIZE * BLOCK_SIZE;
    BPos chunkPos = m_world->getChunkPos(id);

    m_chunks[id] = new WorldChunkDisplayer(
      m_sceneManager->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(
        chunkSize * chunkPos.x,
        chunkSize * chunkPos.y,
        chunkSize * chunkPos.z
      )),
      &m_blockTypes,
      m_world->getChunk(id),
      m_sceneManager
    );
  }
}

static PosRange _getRange(const GameWorld::Event& event)
{
  switch (event.type)
  {
    case GameWorld::SetBlock:
    case GameWorld::RemoveBlock:
      return PosRange::betweenPos(event.blockPos, event.blockPos);
    break;

    case GameWorld::SetBlockRange:
    case GameWorld::RemoveBlockRange:
      return PosRange::betweenPos(event.blockPos, event.blockPos2);
    break;

    case GameWorld::EventCount:
    break;
  }
  assert(false);
}

void GameWorldDisplayer::applyEvent(const GameWorld::Event& event)
{
  // FIXME
  BlockType blockType = (event.type == GameWorld::RemoveBlock || event.type == GameWorld::RemoveBlockRange) ? BlockType::AIR : event.blockType;

  for (const auto& slice : m_world->sliceArea(_getRange(event)))
    for (BPos pos : slice.posRange)
      m_chunks[slice.chunkId]->setBlock(pos, blockType);
}

Ogre::SceneManager* GameWorldDisplayer::getScene()
{
  return m_sceneManager;
}
