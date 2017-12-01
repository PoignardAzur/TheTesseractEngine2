
#ifndef H_GAME_WORLD_DISPLAYER
#define H_GAME_WORLD_DISPLAYER

class GameWorldDisplayer
{
public:
  GameWorldDisplayer(const GameWorld& world);

  void applyEvent(const Event& event);

  Ogre::SceneManager* getScene();

private:

  Ogre::SceneManager* m_sceneManager;
  std::map<BlockType, std::string> m_blockTypes;
  std::deque<size_t> m_chunkIds;
  std::map<size_t, WorldAreaDisplayer*> m_chunks;
};

#endif // !H_GAME_WORLD_DISPLAYER
