
#include "SfmlInputs.hpp"

SfmlInputs::SfmlInputs(sf::Window* window, unsigned seed) :
  _window(window),
  _rng(seed)
{
}

Inputs::Rng& SfmlInputs::getRng()
{
  return _rng;
}

static void _applyEvent(
  Inputs::State& state,
  Inputs::Events& events,
  const sf::Event& event
) {
  switch (event.type) {
    case sf::Event::Closed:
      state.windowClosed = true;
    break;

    case sf::Event::Resized:
      events.windowResized = true;
      state.windowSize = { event.size.width, event.size.height };
    break;

    case sf::Event::LostFocus:
      events.windowLostFocus = true;
      state.windowHasFocus = false;
    break;

    case sf::Event::GainedFocus:
      events.windowGainedFocus = true;
      state.windowHasFocus = true;
    break;

    case sf::Event::KeyPressed:
    {
      auto key = event.key.code;
      bool firstTime = !state.keysDown[key];

      events.keysPressed[key] = true;
      events.keysReleased[key] = false;
      if (firstTime)
        events.keysFirstPressed[key] = true;
      state.keysDown[key] = true;
    }
    break;
    case sf::Event::KeyReleased:
    {
      auto key = event.key.code;

      events.keysPressed[key] = false;
      events.keysFirstPressed[key] = false;
      events.keysReleased[key] = true;
      state.keysDown[event.key.code] = false;
    }
    break;
    case sf::Event::MouseButtonPressed:
    {
      auto button = event.mouseButton.button;
      bool firstTime = !state.mouseButtonsDown[button];

      events.mouseButtonsPressed[button] = true;
      events.mouseButtonsReleased[button] = false;
      if (firstTime)
        events.mouseButtonsFirstPressed[button] = true;
      state.mouseButtonsDown[button] = true;
    }
    break;
    case sf::Event::MouseButtonReleased:
    {
      auto button = event.mouseButton.button;

      events.mouseButtonsPressed[button] = false;
      events.mouseButtonsFirstPressed[button] = false;
      events.mouseButtonsReleased[button] = true;
      state.mouseButtonsDown[button] = false;
    }
    break;

    case sf::Event::MouseMoved:
    {
      sf::Vector2f newPos(event.mouseMove.x, event.mouseMove.y);

      events.mouseMoved = true;
      events.cursorMovement += newPos - state.cursorPosition;
      state.cursorPosition = newPos;
    }
    break;

    default:
    break;
  }
}

void SfmlInputs::wait(State& state, Events& events, bool centerMouse) {
  sf::Event event;
  _window->waitEvent(event);
  _applyEvent(state, events, event);

  poll(state, events, centerMouse);
}

void SfmlInputs::poll(State& state, Events& events, bool centerMouse) {
  sf::Event event;

  while (_window->pollEvent(event)) {
    _applyEvent(state, events, event);
  }

  if (state.windowHasFocus && centerMouse) {
    sf::Mouse::setPosition(sf::Vector2i(_window->getSize() / 2u), *_window);
    state.cursorPosition = sf::Vector2f(_window->getSize() / 2u);
  }
}
