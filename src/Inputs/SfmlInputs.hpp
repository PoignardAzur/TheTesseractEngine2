
#ifndef H_SFML_INPUTS
#define H_SFML_INPUTS

#include "Inputs.hpp"

#include <random>

class SfmlInputs : public Inputs
{
public:
  SfmlInputs(sf::Window* window, unsigned seed);

  Rng& getRng();
  void wait(State& state, Events& events, bool centerMouse);
  void poll(State& state, Events& events, bool centerMouse);

private:
  sf::Window* _window;
  Rng _rng;
};

#endif // !H_SFML_INPUTS
