
#include "GameScene.hpp"

GameScene::GameScene()
{
  WorldArea area({3, 3, 3});
  for (BPos pos : area.getPosRange())
    area.setBlock(pos, ((pos.x ^ pos.y ^ pos.z) % 2 == 0) ? BlockType::DIRT : BlockType::STONE);

  m_world.reset(new GameWorld(std::move(area)));
  m_worldDisplayer.reset(new GameWorldDisplayer(*m_world));

  m_player.setPosition(EPos(26, 26, 26));
  m_player.lookAt(EPos(0, 0, 0));
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
  auto playerEvents = m_player.gameUpdate(inputState, inputEvents, rng);
  for (const GameWorld::Event& event : playerEvents)
  {
    m_world->applyEvent(event);
    m_worldDisplayer->applyEvent(event);
  }
}

static Ogre::Vector3 _EPosToOgre(EPos p)
{
  return Ogre::Vector3(
    p.x * BLOCK_SIZE,
    p.y * BLOCK_SIZE,
    p.z * BLOCK_SIZE
  );
}

void GameScene::displayUpdate(
  Ogre::RenderWindow* window,
  const Inputs::State& inputState
)
{
  // TODO
  // m_worldDisplayer->update(dt);

  Ogre::SceneManager* scene = m_worldDisplayer->getScene();
  Ogre::Camera* camera = scene->getCamera("cam");
  camera->setNearClipDistance(5);

  //m_player.displayUpdate(dt);
  camera->setPosition(_EPosToOgre(m_player.getPosition()));
  camera->setOrientation(m_player.getOrientation());

  window->removeAllViewports();
  Ogre::Viewport *viewport = window->addViewport(camera);
  viewport->setBackgroundColour(Ogre::ColourValue(1, 1, 1));

  camera->setAspectRatio(
    Ogre::Real(viewport->getActualWidth()) /
    Ogre::Real(viewport->getActualHeight())
  );
}

bool GameScene::isOver()
{
  return false;
}
