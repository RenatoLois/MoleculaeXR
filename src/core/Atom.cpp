#include "core/Atom.hpp"

unsigned int Atom::getCharge() const {
  return this->Z - this->Q;
}

