
#ifndef H_SCENE
#define H_SCENE

#include <Ogre.h>
#include "Inputs.hpp"

class Scene
{
public:
  virtual void gameUpdate(
    const Inputs::State& inputState,
    const Inputs::Events& inputEvents,
    Inputs::Rng& rng
  )
  {}

  virtual void displayUpdate(
    Ogre::RenderWindow* window, const Inputs::State& inputState
  )
  {}

  virtual bool isOver()
  {
    return false;
  }
};

#endif // !H_SCENE
