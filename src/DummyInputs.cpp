
#include "DummyInputs.hpp"

DummyInputs::DummyInputs(unsigned seed) :
  _rng(seed)
{
}

Inputs::Rng& DummyInputs::getRng()
{
  return _rng;
}

void DummyInputs::poll(State& state, Events& events) {
  (void)state;
  (void)events;
}
