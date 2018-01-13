
#ifndef H_GAME_SCENE
#define H_GAME_SCENE

#include <Ogre.h>

#include "Scene.hpp"

#include "GameWorld/GameWorld.hpp"
#include "GameWorldDisplayer/GameWorldDisplayer.hpp"
#include "FloatingPlayer.hpp"

class GameScene : public Scene
{
public:
  GameScene();

  void gameUpdate(
    const Inputs::State& inputState,
    const Inputs::Events& inputEvents,
    Inputs::Rng& rng
  );
  void displayUpdate(
    Ogre::RenderWindow* window,
    const Inputs::State& inputState
  );

  bool isOver();

private:
  GameWorld::Ptr m_world;
  GameWorldDisplayer::Ptr m_worldDisplayer;
  FloatingPlayer m_player;
};

#endif // !H_GAME_SCENE
