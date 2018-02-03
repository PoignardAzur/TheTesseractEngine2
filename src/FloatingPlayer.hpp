
#ifndef H_FLOATING_PLAYER
#define H_FLOATING_PLAYER

#include "GameWorld/EntityPos.hpp"
#include "GameWorld/EntityOrientation.hpp"
#include "GameWorld/GameWorld.hpp"

class FloatingPlayer
{
public:
  FloatingPlayer();

  void setPosition(EPos pos);
  void lookAt(EPos pos);

  void yaw(const Ogre::Radian& angle);
  void pitch(const Ogre::Radian& angle);
  void rotate(const Ogre::Quaternion& q);

  std::deque<GameWorld::Event> gameUpdate(
    const GameWorld& world,
    const Inputs::State& inputState,
    const Inputs::Events& inputEvents,
    Inputs::Rng& rng
  );
  // void displayUpdate(float dt);

  EPos getPosition() const;
  EOrient getOrientation() const;

private:
  EPos m_pos = {};
  EOrient m_orient = {};
};

#endif // !H_FLOATING_PLAYER
