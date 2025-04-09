#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "nucleus.h"
#include "particle.h"

int main()
{
  //to ensure that it is worth keeping header and implementation files separate, going to instantiate the photons here
  Photon p1{0, 0.661, std::vector<std::shared_ptr<Electron>>{}};
  Photon p2{0, 1.275, std::vector<std::shared_ptr<Electron>>{}};
  Photon p3{0, 1.173, std::vector<std::shared_ptr<Electron>>{}};
  Photon p4{0, 1.333, std::vector<std::shared_ptr<Electron>>{}};

  p1.pair_production(p1);
  p2.compton_scattering(p2);
  p3.photoelectric_effect(p3);
  p4.pair_production(p4);

  return 0;
}