
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

    bool windowClosed = false;
    sf::Vector2u windowSize;
    bool windowHasFocus = false;
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

    bool windowResized = false;
    bool windowLostFocus = false;
    bool windowGainedFocus = false;
  };

  virtual Rng& getRng() = 0;
  virtual void wait(State& state, Events& events, bool centerMouse) = 0;
  virtual void poll(State& state, Events& events, bool centerMouse) = 0;
};

#endif // !H_INPUTS
