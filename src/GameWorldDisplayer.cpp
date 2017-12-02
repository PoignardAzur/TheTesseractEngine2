
#include <cassert>
#include "GameWorldDisplayer.hpp"

GameWorldDisplayer::GameWorldDisplayer(const GameWorld& world)
{
  m_sceneManager = Ogre::Root::getSingleton().createSceneManager(
    Ogre::ST_GENERIC, "Scene0"
  );
  m_sceneManager->createCamera("cam");

  m_blockTypes = {
    { BlockType::STONE, "Cube/Stone" },
    { BlockType::DIRT, "Cube/Dirt" }
  };

  m_chunkIds = world.getChunkIds();
  for (size_t id : m_chunkIds)
  {
    float chunkSize = CHUNK_SIZE * BLOCK_SIZE;
    BPos chunkPos = world.getChunkPos(id);

    m_chunks[id] = new WorldAreaDisplayer(
      m_sceneManager->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(
        chunkSize * chunkPos.x,
        chunkSize * chunkPos.y,
        chunkSize * chunkPos.z
      )),
      &m_blockTypes,
      world.getChunk(id),
      m_sceneManager
    );
  }
}

void GameWorldDisplayer::applyEvent(const GameWorld::Event& event)
{
  (void)event;
}

Ogre::SceneManager* GameWorldDisplayer::getScene()
{
  return m_sceneManager;
}
