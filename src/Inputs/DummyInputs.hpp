
#ifndef H_DUMMY_INPUTS
#define H_DUMMY_INPUTS

#include "Inputs.hpp"
#include <random>

class DummyInputs : public Inputs
{
public:
  DummyInputs(unsigned seed);

  Rng& getRng();
  void poll(State& state, Events& events);

private:
  Rng _rng;
};

#endif // !H_DUMMY_INPUTS
