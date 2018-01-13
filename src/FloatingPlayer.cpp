
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
  // TODO
  yaw(Ogre::Degree(-inputEvents.cursorMovement.x * 0.015f));
  pitch(Ogre::Degree(-inputEvents.cursorMovement.y * 0.015f));

  (void)rng;

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
