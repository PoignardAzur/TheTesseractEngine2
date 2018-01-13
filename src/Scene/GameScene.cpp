
#include "GameScene.hpp"

GameScene::GameScene()
{
  WorldArea area;
  for (BPos pos : area.getPosRange())
    area.setBlock(pos, ((pos.x ^ pos.y ^ pos.z) % 2 == 0) ? BlockType::DIRT : BlockType::STONE);

  m_world.reset(new GameWorld(std::move(area)));
  m_worldDisplayer.reset(new GameWorldDisplayer(*m_world));
}

void GameScene::gameUpdate(
  const Inputs::State& inputState,
  const Inputs::Events& inputEvents,
  Inputs::Rng& rng
)
{
  auto gameworldEvents = m_world->getUpdateEvents(rng);
  for (const GameWorld::Event& event : gameworldEvents)
  {
    m_world->applyEvent(event);
    m_worldDisplayer->applyEvent(event);
  }

  // m_player.update(inputState, inputEvents);
}

void GameScene::displayUpdate(
  Ogre::RenderWindow* window,
  const Inputs::State& inputState
)
{
  Ogre::SceneManager* scene = m_worldDisplayer->getScene();
  Ogre::Camera* camera = scene->getCamera("cam");

  camera->setPosition(Ogre::Vector3(260, 260, 260));
  camera->lookAt(Ogre::Vector3(0, 0, 0));
  camera->setNearClipDistance(5);

  // camera->setPosition(m_player.getPosition());
  // camera->setOrientation(m_player.getOrientation());

  window->removeAllViewports();
  Ogre::Viewport *viewport = window->addViewport(camera);
  viewport->setBackgroundColour(Ogre::ColourValue(1, 1, 1));

  camera->setAspectRatio(
    Ogre::Real(viewport->getActualWidth()) /
    Ogre::Real(viewport->getActualHeight())
  );

  // TODO
  // m_worldDisplayer->update(dt);
}

bool GameScene::isOver()
{
  return false;
}
