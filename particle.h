#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <cmath>
#include <utility>

#ifndef PARTICLE_H
#define PARTICLE_H

class Electron;

class Particle
{
protected:
  double rest_mass;
  double energy;

public:
  Particle() : rest_mass{0}, energy{0} {}
  Particle(double m, double e) : rest_mass{m}, energy{e} {}
  Particle(const Particle &p) : rest_mass{p.rest_mass}, energy{p.energy} {}
  Particle(Particle &&p) noexcept : rest_mass{std::move(p.rest_mass)}, energy{std::move(p.energy)} {}

  Particle &operator=(const Particle &p)
  {
    std::cout<<"Copy assignment operator called "<<std::endl;
    if(&p == this) return *this;

    rest_mass = p.rest_mass;
    energy = p.energy;
    return *this;
  }
  Particle &operator=(Particle &&p) noexcept
  {
    std::cout<<"Move assignment operator called "<<std::endl;
    if(this != &p)
    {
      std::swap(rest_mass,p.rest_mass);
      std::swap(energy,p.energy);
    }
    return *this;
  }
  virtual ~Particle() {} //virtual destructor used to avoid errors
  //rule of 5, if you define any constructor/ assignment operator, you should define all of them
  virtual void set_rest_mass(double m) {rest_mass = m;}
  virtual void set_energy(double e) 
  {
    if(e < rest_mass)
    {
      std::cout<<"Error: energy cannot be less than rest mass"<<std::endl;
      energy = rest_mass;
    }
    else
    {
      energy = e;
    }
  }

  virtual double get_rest_mass() const {return rest_mass;}
  virtual double get_energy() const {return energy;}

  virtual void print_data()
  {
    std::cout<<"Rest mass: "<<rest_mass<<" MeV/c^2"<<std::endl;
    std::cout<<"Energy: "<<energy<<" MeV"<<std::endl;
  } //virtual print_data function to be overridden in derived classes 
};


class Photon : public Particle
{
  friend double photonelectric_effect(const Photon &p);
  friend Photon compton_scattering(Photon &p);
  friend std::vector<std::shared_ptr<Electron>> pair_production(Photon &p);

private:
  std::vector<std::shared_ptr<Electron>> pair_prod;
public:
  Photon() : Particle{}, pair_prod{} {}
  Photon(double m, double e, std::vector<std::shared_ptr<Electron>> pp = {}) : Particle{m, e}, pair_prod{pp} {}
  Photon(const Photon &p) : Particle{p.rest_mass, p.energy}, pair_prod{p.pair_prod} {}
  Photon(Photon &&p) noexcept : Particle{std::move(p.rest_mass), std::move(p.energy)}, pair_prod{std::move(p.pair_prod)} {}

  Photon &operator=(const Photon &p)
  {
    std::cout<<"Copy assignment operator called "<<std::endl;
    if(&p == this) return *this;

    rest_mass = p.rest_mass;
    energy = p.energy;
    pair_prod = p.pair_prod;
    return *this;
  }
  Photon &operator=(Photon &&p) noexcept
  {
    std::cout<<"Move assignment operator called "<<std::endl;
    if(this != &p)
    {
      std::swap(rest_mass,p.rest_mass);
      std::swap(energy,p.energy);
      std::swap(pair_prod,p.pair_prod);
    }
    return *this;
  }

  void set_rest_mass() {rest_mass = 0;}
  void set_pair_prod(std::vector<std::shared_ptr<Electron>> pp) {pair_prod = pp;}

  std::vector<std::shared_ptr<Electron>> get_pair_production() {return pair_prod;}

  double photoelectric_effect(const Photon &p) //photoelectric effect
  {
    energy = p.energy;
    std::cout<<"Photon energy: "<<energy<<" MeV"<<std::endl;
    return energy;
  }

  Photon compton_scattering(Photon &p) //compton scattering 
  {
    double E = photoelectric_effect(p);
    double m = 0.511;
    double E_prime = E/(1 + E/m); //theta set to 90 degrees for simplicity 
    std::cout<<"Photon energy after compton scattering: "<<E_prime<<" MeV"<<std::endl;
    p.energy = E_prime;
    return p;
  }

  std::vector<std::shared_ptr<Electron>>& pair_production(Photon &p) //pair production
  {
    double E = p.energy;
    double m = 0.511;
    if(E < 2*m)
    {
      std::cout<<"Error: Photon energy is not sufficient for pair production"<<std::endl;
      return p.pair_prod; //returns empty vector if energy is not sufficient
    }
    else
    {
      std::shared_ptr<Electron> e1 = std::make_shared<Electron>(0.511, E/2);
      std::shared_ptr<Electron> e2 = std::make_shared<Electron>(0.511, E/2);
      p.pair_prod.push_back(e1);
      p.pair_prod.push_back(e2);
      p.energy = 0;
      std::cout<<"Pair production successful"<<std::endl;
      return pair_prod;
    }
  }
};

class Electron : public Particle
{
  friend Photon radiate(Electron &e);

private:
  std::vector<std::shared_ptr<Photon>> radiation;
public:
  Electron() : Particle{}, radiation{} {}
  Electron(double m, double e) : Particle{m,e}, radiation{} {}
  Electron(double m, double e, std::vector<std::shared_ptr<Photon>> rad) : Particle{m,e}, radiation{rad} {}
  Electron(const Electron &e) : Particle{e.rest_mass, e.energy}, radiation{e.radiation} {}
  Electron(Electron &&e) noexcept : Particle{std::move(e.rest_mass), std::move(e.energy)}, radiation{std::move(e.radiation)} {}

  Electron &operator=(const Electron &e)
  {
    std::cout<<"Copy assignment operator called "<<std::endl;
    if(&e == this) return *this;

    rest_mass = e.rest_mass;
    energy = e.energy;
    radiation = e.radiation;
    return *this;
  }
  Electron &operator=(Electron &&e) noexcept
  {
    std::cout<<"Move assignment operator called "<<std::endl;
    if(this != &e)
    {
      std::swap(rest_mass,e.rest_mass);
      std::swap(energy,e.energy);
      std::swap(radiation,e.radiation);
    }
    return *this;
  }

  void set_rest_mass() {rest_mass = 0.511;}
  void set_energy(double e) 
  {
    if(e < rest_mass)
    {
      std::cout<<"Error: energy cannot be less than rest mass"<<std::endl;
      energy = rest_mass;
    }
    else
    {
      energy = e;
    }
  }
  void set_radiation(std::vector<std::shared_ptr<Photon>> rad) {radiation = rad;}

  void get_radiation()
  {
    for(auto &r : radiation)
    {
      std::cout<<"Photon energy: "<<r->get_energy()<<std::endl;
    }
  }

  Photon radiate(Electron &e) //radation function which returns a photon 
  {
    if(e.radiation.empty() && e.energy < 0.511) //ensures that the electron cannot radiate indefinitely
    {
      std::cout<<"Error: No radiation to emit"<<std::endl;
      return Photon{0,0, std::vector<std::shared_ptr<Electron>> {}}; // Return a default photon if no radiation is available
    }
    else
    {
      double E_new = e.energy - 0.511;
      std::shared_ptr<Photon> p_new = std::make_shared<Photon>(0, E_new, std::vector<std::shared_ptr<Electron>>{});
      e.radiation.push_back(p_new); 
      //new photon created to ensure that an electron has to radiate if it has extra energy

      std::shared_ptr<Photon> p = e.radiation.back();
      e.radiation.insert(e.radiation.begin(), p); //inserts the new photon at the start of the vector so its the last to be radiated
      std::cout<<"Radiating photon with energy: "<<p->get_energy()<<std::endl;
      return *p;
    }
  }

};

#endif