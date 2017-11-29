
#include <Ogre.h>
#include <OgreApplicationContext.h>

#include <SFML/Graphics.hpp>

#include <iostream>
#include <chrono>

#include "Inputs.hpp"
#include "Scene.hpp"

// Not sure if this is a code smell
void _load_resources(
  const std::string& configFileName,
  Ogre::ResourceGroupManager* resourceGroupManager
)
{
  Ogre::ConfigFile configFile;
  configFile.load(configFileName.c_str());

  auto configIt = configFile.getSectionIterator();
  while (configIt.hasMoreElements())
  {
      for (const auto& settings : *configIt.getNext())
      {
          Ogre::String resourceArchiveType = settings.first;
          Ogre::String resourcePath = settings.second;

          resourceGroupManager->addResourceLocation(
              resourcePath, resourceArchiveType
          );
      }
  }
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

    Inputs::State inputState;
    Inputs::Events inputEvents;

    m_inputs->poll(inputState, inputEvents);

    if (inputState.isWindowClosed)
      return false;
    if (inputState.keysDown[sf::Keyboard::Escape])
      return false;

    m_scene->gameUpdate(inputState, inputEvents, m_inputs->getRng());
    m_scene->displayUpdate(m_window, inputState);

    return true;
  }

private:
  Ogre::RenderWindow* m_window;

  Inputs* m_inputs;
  Scene* m_scene;
};

int main(int argc, char **argv)
{
  (void)argc;
  (void)argv;

  try
  {
    Ogre::Root ogreRoot("plugins.cfg");

    _load_resources("resources.cfg", &Ogre::ResourceGroupManager::getSingleton());
    //if (!mRoot->restoreConfig() && !mRoot->showConfigDialog()))
    if (!ogreRoot.showConfigDialog())
      return false;
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
    ogreRoot.initialise(false);

    sf::RenderWindow sfmlWindow(
      sf::VideoMode(800, 600), "Ogre3D v1.10 and SFML v2.4.2"
    );

    // ogreWindow points to the same window as sfmlWindow
    // ogreWindow is used for displaying things, sfmlWindow for events
    Ogre::NameValuePairList misc = { { "currentGLContext", "True" } };
    Ogre::RenderWindow* ogreWindow = ogreRoot.createRenderWindow(
      "NameThatShouldNotBeDisplayed", 42, 42, false, &misc
    );

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    Inputs* inputs = new Inputs(&sfmlWindow, seed);
    Scene* scene = new Scene();

    AppFrameListener app(ogreWindow, inputs, scene);
    ogreRoot.addFrameListener(&app);
    ogreRoot.startRendering();
  }
  catch (const std::exception& e)
  {
    std::cerr << "Error occurred during execution: " << e.what() << '\n';
    return 1;
  }

  return 0;
}
