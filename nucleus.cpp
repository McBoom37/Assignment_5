//11011183 05/04/2025
//main function to test the nucleus class 

#include <iostream>
#include <string>
#include <memory>

#include "nucleus.h"
#include "particle.h"

int main()
{
  StableNucleus Fe{56, 26, "Fe"}; //instantiating the nuclei
  RadioactiveNucleus Co{60, 27, "Co", 5.27, false, nullptr};
  RadioactiveNucleus Na{23, 11, "Na", 2.6, false, nullptr};
  RadioactiveNucleus Cs{137, 55, "Cs", 30.17, false, nullptr};

  Fe.print_data();
  Co.print_data();
  Na.print_data();
  Cs.print_data();

  Co.decay(Co); //testing the decay function
  Cs.decay(Cs);
  Na.decay(Na);

  return 0;
}