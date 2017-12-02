
#ifndef H_GAME_SCENE
#define H_GAME_SCENE

#include <Ogre.h>

#include "Scene.hpp"
#include "GameWorld.hpp"
#include "GameWorldDisplayer.hpp"
// #include "Cameraman.hpp"

class GameScene : public Scene
{
public:
  // FIXME - Remove window argument
  GameScene(Ogre::RenderWindow* window);

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
  // FloatingPlayer m_player;
};

#endif // !H_GAME_SCENE
