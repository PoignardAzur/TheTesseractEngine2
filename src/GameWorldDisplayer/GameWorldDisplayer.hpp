
#ifndef H_GAME_WORLD_DISPLAYER
#define H_GAME_WORLD_DISPLAYER

#include <Ogre.h>

#include <deque>
#include <map>
#include <memory>

#include "GameWorld/GameWorld.hpp"
#include "WorldChunkDisplayer.hpp"

class GameWorldDisplayer
{
public:
  GameWorldDisplayer(const GameWorld* world);

  void applyEvent(const GameWorld::Event& event);

  Ogre::SceneManager* getScene();

  using Ptr = std::unique_ptr<GameWorldDisplayer>;

private:
  const GameWorld* m_world;

  Ogre::SceneManager* m_sceneManager;
  std::map<BlockType, std::string> m_blockTypes;
  std::deque<size_t> m_chunkIds;
  std::map<size_t, WorldChunkDisplayer*> m_chunks;
};

#endif // !H_GAME_WORLD_DISPLAYER
