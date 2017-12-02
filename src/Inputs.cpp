
#include "Inputs.hpp"

Inputs::Inputs(sf::Window* window, unsigned seed) :
_window(window),
_rng(seed)
{
}

Inputs::Rng& Inputs::getRng()
{
  return _rng;
}

void Inputs::poll(State& state, Events& events) {
  sf::Event event;

  while (_window->pollEvent(event)) {
    switch (event.type) {
      case sf::Event::Closed:
        _state.isWindowClosed = true;
      break;

      case sf::Event::KeyPressed:
      {
        auto key = event.key.code;
        bool firstTime = !_state.keysDown[key];

        events.keysPressed[key] = true;
        events.keysReleased[key] = false;
        if (firstTime)
          events.keysFirstPressed[key] = true;
        _state.keysDown[key] = true;
      }
      break;
      case sf::Event::KeyReleased:
      {
        auto key = event.key.code;

        events.keysPressed[key] = false;
        events.keysFirstPressed[key] = false;
        events.keysReleased[key] = true;
        _state.keysDown[event.key.code] = false;
      }
      break;
      case sf::Event::MouseButtonPressed:
      {
        auto button = event.mouseButton.button;
        bool firstTime = !_state.mouseButtonsDown[button];

        events.mouseButtonsPressed[button] = true;
        events.mouseButtonsReleased[button] = false;
        if (firstTime)
          events.mouseButtonsFirstPressed[button] = true;
        _state.mouseButtonsDown[button] = true;
      }
      break;
      case sf::Event::MouseButtonReleased:
      {
        auto button = event.mouseButton.button;

        events.mouseButtonsPressed[button] = false;
        events.mouseButtonsFirstPressed[button] = false;
        events.mouseButtonsReleased[button] = true;
        _state.mouseButtonsDown[button] = false;
      }
      break;

      case sf::Event::MouseMoved:
      {
        sf::Vector2f newPos(event.mouseMove.x, event.mouseMove.y);

        events.mouseMoved = true;
        events.cursorMovement += newPos - _state.cursorPosition;
        _state.cursorPosition = newPos;
      }
      break;
    }
  }
  state = _state;
}
