//11011183 05/04/2025
//main function to test the nucleus class 

#include <iostream>
#include <string>
#include <memory>

#include "nucleus.h"
#include "particle.h"

int main()
{
  StableNucleus Fe{56, 26, "Fe"};
  RadioactiveNucleus Co{60, 27, "Co", 5.27, false, nullptr};
  RadioactiveNucleus Na{23, 11, "Na", 2.6, false, nullptr};
  RadioactiveNucleus Cs{137, 55, "Cs", 30.17, false, nullptr};

  Photon photon(0.0, 10.0, std::vector<std::shared_ptr<Electron>>{});

  Fe.print_data();
  Co.print_data();
  Na.print_data();
  Cs.print_data();

  Co.decay(Co);



  return 0;
}