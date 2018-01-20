
#include "FloatingPlayer.hpp"

FloatingPlayer::FloatingPlayer()
{
}


void FloatingPlayer::setPosition(EPos pos)
{
  m_pos = pos;
}

void FloatingPlayer::lookAt(EPos pos)
{
  EPos dpos = pos - m_pos;

  if (dpos == Ogre::Vector3::ZERO)
    return;

  Ogre::Vector3 zAdjustVec = -dpos;
  zAdjustVec.normalise();

  Ogre::Vector3 xVec = Ogre::Vector3::UNIT_Y.crossProduct(zAdjustVec);
  xVec.normalise();
  Ogre::Vector3 yVec = zAdjustVec.crossProduct(xVec);
  yVec.normalise();

  Ogre::Quaternion targetWorldOrientation;
  targetWorldOrientation.FromAxes(xVec, yVec, zAdjustVec);
  m_orient = targetWorldOrientation;
}

void FloatingPlayer::yaw(const Ogre::Radian& angle)
{
  Ogre::Vector3 yAxis = Ogre::Vector3::UNIT_Y;
  rotate(Ogre::Quaternion(angle, yAxis));
}

void FloatingPlayer::pitch(const Ogre::Radian& angle)
{
  Ogre::Vector3 xAxis = m_orient * Ogre::Vector3::UNIT_X;
  rotate(Ogre::Quaternion(angle, xAxis));
}

void FloatingPlayer::rotate(const Ogre::Quaternion& q)
{
  Ogre::Quaternion qnorm = q;
  qnorm.normalise();
  m_orient = qnorm * m_orient;
}

std::deque<GameWorld::Event> FloatingPlayer::gameUpdate(
  const Inputs::State& inputState,
  const Inputs::Events& inputEvents,
  Inputs::Rng& rng
)
{
  (void)rng;

  float sensitivity = 0.06f;
  float speed = 1.0f;

  yaw(Ogre::Degree(-inputEvents.cursorMovement.x * sensitivity));
  pitch(Ogre::Degree(-inputEvents.cursorMovement.y * sensitivity));

  Ogre::Vector3 dir = m_orient * -Ogre::Vector3::UNIT_Z;
  Ogre::Vector3 forward = Ogre::Vector3(dir.x, 0, dir.z).normalisedCopy();
  Ogre::Vector3 right = m_orient * Ogre::Vector3::UNIT_X;

  Ogre::Vector3 dpos(0.f);

  if (inputState.keysDown[sf::Keyboard::Z])
    dpos += speed * forward;
  if (inputState.keysDown[sf::Keyboard::Q])
    dpos -= speed * right;
  if (inputState.keysDown[sf::Keyboard::S])
    dpos -= speed * forward;
  if (inputState.keysDown[sf::Keyboard::D])
    dpos += speed * right;

  m_pos += dpos;

  return {};
}

// void FloatingPlayer::displayUpdate(float dt);

EPos FloatingPlayer::getPosition() const
{
  return m_pos;
}

EOrient FloatingPlayer::getOrientation() const
{
  return m_orient;
}
