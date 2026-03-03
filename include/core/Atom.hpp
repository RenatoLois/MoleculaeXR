#pragma once


class Atom {
public:
  unsigned int Z;  // atomic number
  unsigned int Q;  // number of eletrons
  unsigned int A;  // atomic weight

  unsigned int getCharge() const;
};
