
#include <Ogre.h>
#include <OgreApplicationContext.h>

#include <SFML/Graphics.hpp>

#include <iostream>
#include <chrono>
#include <cassert>

#include "Inputs/SfmlInputs.hpp"
#include "Inputs/DummyInputs.hpp"
#include "Scene/GameScene.hpp"

// Not sure if this is a code smell
void _load_resources(
  const std::string& configFileName,
  Ogre::ResourceGroupManager* resourceGroupManager
)
{
  Ogre::ConfigFile configFile;
  configFile.load(configFileName.c_str());

  for (const auto& section : configFile.getSettingsBySection())
  {
      for (const auto& settings : section.second)
      {
          Ogre::String resourceArchiveType = settings.first;
          Ogre::String resourcePath = settings.second;

          resourceGroupManager->addResourceLocation(
              resourcePath, resourceArchiveType
          );
      }
  }
}

void _createCubeMesh()
{
  Ogre::ManualObject cube("Cube_obj");

  cube.begin("Cube/Dirt");

  cube.position(0.5, -0.5, 1.0);
  cube.normal(0.408248, -0.816497, 0.408248);
  cube.textureCoord(1, 0);

  cube.position(-0.5, -0.5, 0.0);
  cube.normal(-0.408248, -0.816497, -0.408248);
  cube.textureCoord(0, 1);

  cube.position(0.5, -0.5, 0.0);
  cube.normal(0.666667, -0.333333, -0.666667);
  cube.textureCoord(1, 1);

  cube.position(-0.5, -0.5, 1.0);
  cube.normal(-0.666667, -0.333333, 0.666667);
  cube.textureCoord(0, 0);

  cube.position(0.5, 0.5, 1.0);
  cube.normal(0.666667, 0.333333, 0.666667);
  cube.textureCoord(1, 0);

  cube.position(-0.5, -0.5, 1.0);
  cube.normal(-0.666667, -0.333333, 0.666667);
  cube.textureCoord(0, 1);

  cube.position(0.5, -0.5, 1.0);
  cube.normal(0.408248, -0.816497, 0.408248);
  cube.textureCoord(1, 1);

  cube.position(-0.5, 0.5, 1.0);
  cube.normal(-0.408248, 0.816497, 0.408248);
  cube.textureCoord(0, 0);

  cube.position(-0.5, 0.5, 0.0);
  cube.normal(-0.666667, 0.333333, -0.666667);
  cube.textureCoord(0, 1);

  cube.position(-0.5, -0.5, 0.0);
  cube.normal(-0.408248, -0.816497, -0.408248);
  cube.textureCoord(1, 1);

  cube.position(-0.5, -0.5, 1.0);
  cube.normal(-0.666667, -0.333333, 0.666667);
  cube.textureCoord(1, 0);

  cube.position(0.5, -0.5, 0.0);
  cube.normal(0.666667, -0.333333, -0.666667);
  cube.textureCoord(0, 1);

  cube.position(0.5, 0.5, 0.0);
  cube.normal(0.408248, 0.816497, -0.408248);
  cube.textureCoord(1, 1);

  cube.position(0.5, -0.5, 1.0);
  cube.normal(0.408248, -0.816497, 0.408248);
  cube.textureCoord(0, 0);

  cube.position(0.5, -0.5, 0.0);
  cube.normal(0.666667, -0.333333, -0.666667);
  cube.textureCoord(1, 0);

  cube.position(-0.5, -0.5, 0.0);
  cube.normal(-0.408248, -0.816497, -0.408248);
  cube.textureCoord(0, 0);

  cube.position(-0.5, 0.5, 1.0);
  cube.normal(-0.408248, 0.816497, 0.408248);
  cube.textureCoord(1, 0);

  cube.position(0.5, 0.5, 0.0);
  cube.normal(0.408248, 0.816497, -0.408248);
  cube.textureCoord(0, 1);

  cube.position(-0.5, 0.5, 0.0);
  cube.normal(-0.666667, 0.333333, -0.666667);
  cube.textureCoord(1, 1);

  cube.position(0.5, 0.5, 1.0);
  cube.normal(0.666667, 0.333333, 0.666667);
  cube.textureCoord(0, 0);

  cube.triangle(0, 1, 2);
  cube.triangle(3, 1, 0);
  cube.triangle(4, 5, 6);
  cube.triangle(4, 7, 5);
  cube.triangle(8, 9, 10);
  cube.triangle(10, 7, 8);
  cube.triangle(4, 11, 12);
  cube.triangle(4, 13, 11);
  cube.triangle(14, 8, 12);
  cube.triangle(14, 15, 8);
  cube.triangle(16, 17, 18);
  cube.triangle(16, 19, 17);
  cube.end();

  cube.convertToMesh("Cube_mesh");
}

class AppFrameListener : public Ogre::FrameListener
{
public:
  AppFrameListener(Ogre::RenderWindow* window, Inputs* inputs, Scene* scene)
  {
    m_window = window;
    m_inputs = inputs;
    m_scene = scene;
  }

  bool frameRenderingQueued(const Ogre::FrameEvent &evt)
  {
    if (m_scene->isOver())
      return false;

    Inputs::Events inputEvents;

    m_inputs->poll(m_inputState, inputEvents);

    if (m_inputState.isWindowClosed)
      return false;
    if (m_inputState.keysDown[sf::Keyboard::Escape])
      return false;

    m_scene->gameUpdate(m_inputState, inputEvents, m_inputs->getRng());
    m_scene->displayUpdate(m_window, m_inputState);

    return true;
  }

private:
  Ogre::RenderWindow* m_window;

  Inputs* m_inputs;
  Scene* m_scene;

  Inputs::State m_inputState;
};

int main(int argc, char **argv)
{
  (void)argc;
  (void)argv;

  try
  {
    Ogre::Root ogreRoot("plugins.cfg");

    _load_resources("resources.cfg", &Ogre::ResourceGroupManager::getSingleton());
    // if (!mRoot->restoreConfig() && !mRoot->showConfigDialog(new Ogre::ConfigDialog)))
    if (!ogreRoot.showConfigDialog(nullptr))
      return 1;
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
    ogreRoot.initialise(false);

    sf::ContextSettings settings;
    settings.depthBits = 32;
    sf::Window sfmlWindow(
      sf::VideoMode(800, 600),
      "Ogre3D v1.10 and SFML v2.4.2",
      sf::Style::Default,
      settings
    );

    sfmlWindow.setFramerateLimit(30);
    sfmlWindow.setMouseCursorGrabbed(true);

    Ogre::NameValuePairList params = {
      { "externalGLControl", "true" },
      { "currentGLContext", "true" }
    };
    // sfmlWindow points to the same window as ogreWindow
    // ogreWindow is used for displaying things, sfmlWindow for events
    Ogre::RenderWindow* ogreWindow = ogreRoot.createRenderWindow(
      "FAKENAME", 42, 42, false, &params
    );

    _createCubeMesh();

    Scene* scene = new GameScene();

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    Inputs* inputs = new SfmlInputs(&sfmlWindow, seed);
    // Inputs* inputs = new DummyInputs(seed);

    AppFrameListener app(ogreWindow, inputs, scene);
    ogreRoot.addFrameListener(&app);

    while (true)
    {
      if (!ogreRoot.renderOneFrame())
        break;
      sfmlWindow.display();
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << "Error occurred during execution: " << e.what() << '\n';
    return 1;
  }

  return 0;
}
