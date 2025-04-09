//11011183 05/04/2025
//main function to test the particle class 

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

  p1.pair_production(p1); //testing the photon functions 
  p2.compton_scattering(p2);
  p3.photoelectric_effect(p3);

  std::vector<std::shared_ptr<Electron>> test_electrons = p4.pair_production(p4);
  Electron e1 = *test_electrons[0];
  e1.radiate(e1); //testing the electron functions

  return 0;
}