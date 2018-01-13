
#ifndef H_INPUTS
#define H_INPUTS

// TODO - Move to SfmlInputs
#include <SFML/Graphics.hpp>

#include <array>
#include <random>

class Inputs
{
public:
  using Rng = std::default_random_engine;

  // TODO - enum Action : size_t

  struct State
  {
    std::array<bool, sf::Keyboard::KeyCount> keysDown = {};
    std::array<bool, sf::Mouse::ButtonCount> mouseButtonsDown = {};
    sf::Vector2f cursorPosition;
    bool isWindowClosed = false;
  };

  struct Events
  {
    std::array<bool, sf::Keyboard::KeyCount> keysPressed = {};
    std::array<bool, sf::Mouse::ButtonCount> mouseButtonsPressed = {};
    std::array<bool, sf::Keyboard::KeyCount> keysFirstPressed = {};
    std::array<bool, sf::Mouse::ButtonCount> mouseButtonsFirstPressed = {};
    std::array<bool, sf::Keyboard::KeyCount> keysReleased = {};
    std::array<bool, sf::Mouse::ButtonCount> mouseButtonsReleased = {};

    bool mouseMoved = false;
    sf::Vector2f cursorMovement;
    // TODO
    // bool windowResized = false;
    // sf::Vector2f newWindowSize;
  };

  virtual Rng& getRng() = 0;
  virtual void poll(State& state, Events& events) = 0;
};

#endif // !H_INPUTS
