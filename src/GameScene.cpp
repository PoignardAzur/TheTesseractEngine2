
#include "GameScene.hpp"

GameScene::GameScene()
{
  m_world = new GameWorld();
  // m_world.fillWithStuff;

  m_worldDisplayer = new GameWorldDisplayer(*m_world);
}

void GameScene::gameUpdate(
  const Inputs::State& inputState,
  const Inputs::Events& inputEvents,
  Inputs::Rng& rng
)
{
  auto gameworldEvents = m_world->getUpdateEvents(rng);
  for (const Event& event : gameworldEvents)
  {
    m_world->applyEvent(event);
    m_worldDisplayer->applyEvent(event);
  }

  m_player.update(inputState, inputEvents);
}

void GameScene::displayUpdate(
  Ogre::RenderWindow* window,
  const Inputs::State& inputState
)
{
  Ogre::SceneManager* scene = m_worldDisplayer->getScene();
  Ogre::Camera* camera = scene.getCamera("cam");

  camera.setPosition(100, 100, 100);
  camera.lookAt(0, 0, 0);

  /*
  camera.setPosition(m_player.getPosition());
  camera.setOrientation(m_player.getOrientation());
  */

  window.removeAllViewports();
  window.addViewport(camera);

  // TODO
  // m_worldDisplayer.update(dt);
}

bool isOver()
{
  return false;
}
