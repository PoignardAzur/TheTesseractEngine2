
#include "DummyInputs.hpp"

DummyInputs::DummyInputs(unsigned seed) :
  _rng(seed)
{
}

Inputs::Rng& DummyInputs::getRng()
{
  return _rng;
}

void DummyInputs::wait(State& state, Events& events, bool centerMouse) {
  (void)state;
  (void)events;
  (void)centerMouse;
}

void DummyInputs::poll(State& state, Events& events, bool centerMouse) {
  (void)state;
  (void)events;
  (void)centerMouse;
}
