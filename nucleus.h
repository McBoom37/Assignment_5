//11011183 05/04/2025
//header files for the nucleus class and derived classes, also with a probability-based decay function

#include <iostream>
#include <string>
#include <memory>
#include <random>

std::random_device rd; //random number generators used for decay proababilities 
std::mt19937 gen(rd());
std::uniform_real_distribution<> dis(0.0, 1.0);

#ifndef NUCLEUS_H
#define NUCLEUS_H

#include "particle.h"

class Nucleus
{
protected:
  double atomic_mass;
  double atomic_number;
  std::string nucleus_type;

public:
//should be easy to see which constructor is which here 
  Nucleus() {}
  Nucleus(double a_mass, double a_number, std::string n_type) : atomic_mass(a_mass), atomic_number(a_number), nucleus_type(n_type) {}
  Nucleus(Nucleus &n) : atomic_mass(n.atomic_mass), atomic_number(n.atomic_number), nucleus_type(n.nucleus_type) {}

  Nucleus(Nucleus &&n) : atomic_mass(std::move(n.atomic_mass)), atomic_number(std::move(n.atomic_number)), nucleus_type(std::move(n.nucleus_type)) {}

  Nucleus &operator=(Nucleus &n)
  {
    std::cout<<"Copy assignment operator called "<<std::endl;
    if(&n == this) return *this;

    atomic_mass = n.atomic_mass;
    atomic_number = n.atomic_number;
    nucleus_type = n.nucleus_type;
    return *this;
  }

  Nucleus &operator=(Nucleus &&n)
  {
    std::cout<<"Move assignment operator called "<<std::endl;
    if(this != &n)
    {
      std::swap(atomic_mass,n.atomic_mass);
      std::swap(atomic_number,n.atomic_number);
      std::swap(nucleus_type,n.nucleus_type);
    }
    return *this;
  }
  //my understanding of the rule of 5 is that if you define any constructor/ assignment operator, you should define all of them 

  virtual ~Nucleus(){} //virtual destructor used to avoid errors 

  virtual void set_atomic_mass(double a_mass) {atomic_mass = a_mass;}
  virtual void set_atomic_number(double a_number) {atomic_number = a_number;}
  virtual void set_nucleus_type(std::string n_type) //restrciting general nucleus type 
  {
    if(n_type != "Fe" && n_type != "Co" && n_type != "Na" && n_type != "Cs")
    {
      std::cout<<"Error: invalid nucleus type, setting to default (Fe)"<<std::endl;
      nucleus_type = "Fe";
    }
    else
    {
      nucleus_type = n_type;
    }
  }

  virtual double get_atomic_mass() const {return atomic_mass;}
  virtual double get_atomic_number() const {return atomic_number;}
  virtual std::string get_nucleus_type() const {return nucleus_type;}

  virtual void print_data()
  {
    std::cout<<"Atomic mass: "<<atomic_mass<<std::endl;
    std::cout<<"Atomic number: "<<atomic_number<<std::endl;
    std::cout<<"Nucleus type: "<<nucleus_type<<std::endl;
  }
  //virtual setters/ getters to avoid repitition of code 
};

class StableNucleus : public Nucleus
{
public:
  StableNucleus() {}
  StableNucleus(double a_mass, double a_number, std::string n_type) : Nucleus{a_mass, a_number, n_type} {}
  
  StableNucleus(StableNucleus &s) : Nucleus{s.atomic_mass, s.atomic_number, s.nucleus_type}{}
  StableNucleus(StableNucleus &&s) : Nucleus{std::move(s.atomic_mass), std::move(s.atomic_number), std::move(s.nucleus_type)} {}

  StableNucleus &operator=(StableNucleus &s)
  {
    std::cout<<"Copy assignment operator called "<<std::endl;
    if(&s == this) return *this;

    atomic_mass = s.atomic_mass;
    atomic_number = s.atomic_number;
    nucleus_type = s.nucleus_type;
    return *this;
  }

  StableNucleus &operator=(StableNucleus &&s)
  {
    std::cout<<"Move assignment operator called "<<std::endl;
    if(this != &s)
    {
      std::swap(atomic_mass,s.atomic_mass);
      std::swap(atomic_number,s.atomic_number);
      std::swap(nucleus_type,s.nucleus_type);
    }
    return *this;
  }
  //rule of 5 again 

  void set_nucleus_type(std::string n_type) //restricting type of stable nucleus only to iron
  {
    if(n_type != "Fe")
    {
      std::cout<<"Error: invalid stable nucleus type, setting to default (Fe)"<<std::endl;
      nucleus_type = "Fe";
    }
    else
    {
      nucleus_type = n_type;
    }
  }


};

class RadioactiveNucleus : public Nucleus
{

  friend Photon decay(RadioactiveNucleus &r); //friend function to access private members of the class

private: //extra members 
  double half_life;
  bool decayed;
  std::shared_ptr<Photon> photon;

public:
  RadioactiveNucleus() {}
  RadioactiveNucleus(double a_mass, double a_number, std::string n_type, double hl, bool d, std::shared_ptr<Photon> p) : 
    Nucleus{a_mass, a_number, n_type} , half_life{hl}, decayed{d}, photon{p} {}

  RadioactiveNucleus(RadioactiveNucleus &r) : Nucleus{r.atomic_mass, r.atomic_number, r.nucleus_type},
    half_life(r.half_life), decayed(r.decayed), photon{r.photon} {}
  RadioactiveNucleus(RadioactiveNucleus &&r) : Nucleus{std::move(r.atomic_mass), std::move(r.atomic_number), std::move(r.nucleus_type)},
    half_life(std::move(r.half_life)), decayed(std::move(r.decayed)), photon{std::move(r.photon)} {}

  RadioactiveNucleus &operator=(RadioactiveNucleus &r)
  {
    std::cout<<"Copy assignment operator called: "<<std::endl;
    if(&r == this) return *this;

    atomic_mass = r.atomic_mass;
    atomic_number = r.atomic_number;
    nucleus_type = r.nucleus_type;
    half_life= r.half_life;
    decayed = r.decayed;
    photon = r.photon;
    return *this; 
  }

  RadioactiveNucleus &operator=(RadioactiveNucleus &&r)
  {
    std::cout<<"Move assignment operator called: "<<std::endl;
    if(this != &r)
    {
      std::swap(atomic_mass,r.atomic_mass);
      std::swap(atomic_number,r.atomic_number);
      std::swap(nucleus_type,r.nucleus_type);
      std::swap(half_life,r.half_life);
      std::swap(decayed,r.decayed);
      std::swap(photon,r.photon);
    }
    return *this;
  }

  void set_half_life(double hl) {half_life = hl;}
  void set_decayed() {decayed = false;}
  void set_nucleus_type(std::string n_type) //restricting radioactive nucleus types 
  {
    if(n_type != "Co" && n_type != "Na" && n_type != "Cs")
    {
      std::cout<<"Error: invalid radioactive nucleus type, setting to default (Co)"<<std::endl;
      nucleus_type = "Co";
    }
    else
    {
      nucleus_type = n_type;
    }
  }
  void set_photon(std::shared_ptr<Photon> p) {photon = p;}

  double get_half_life() const {return half_life;}
  double get_decayed() const {return decayed;}
  std::shared_ptr<Photon>& get_photon() {return photon;}

  void print_data() //function overriding on the print_data function 
  {
    std::cout<<std::boolalpha;
    std::cout<<"Atomic mass: "<<atomic_mass<<std::endl;
    std::cout<<"Atomic number: "<<atomic_number<<std::endl;
    std::cout<<"Nucleus type: "<<nucleus_type<<std::endl;
    std::cout<<"Half life: "<<half_life<<" years"<<std::endl;
    std::cout<<"Decayed: "<<decayed<<std::endl;
    std::cout<<std::endl;
  }

  std::vector<Photon> decay(RadioactiveNucleus &r)//vector function so that its possible to return multiple photons
  {
    std::vector<Photon> photons; 
    if(r.decayed == true) //first check whether nucleus has decayed 
    {
      std::cout<<"Error: nucleus has already decayed"<<std::endl;
      return photons; //return empty vector if nucleus has already decayed 
    }
    else
    {
      if(r.nucleus_type == "Na")
      {
        double prob = dis(gen); //incorporating the chance of the decays 
        Photon p1(0, 1274.5, std::vector<std::shared_ptr<Electron>>{});
        if(prob <0.902)
        {
          std::cout<<"Nucleus has decayed into a positron, it will now decay to a photon"<<std::endl;
          Electron positron{0.511, 0.511, std::vector<std::shared_ptr<Photon>>{}};
          p1.set_pair_prod(std::vector<std::shared_ptr<Electron>>{std::make_shared<Electron>(positron)}); //adding zero kinetic energy positron into the photon
        }
        r.decayed = true;
        std::cout<<"Nucleus has decyaed into a photon"<<std::endl;
        photons.push_back(p1);
        r.photon = std::make_shared<Photon>(p1); 
        r.photon->print_data();
        return photons;
      }
      else if(r.nucleus_type == "Cs") //filtering the type of nucleus
      {
        double prob = dis(gen);
        if(prob < 0.946)
        {
          std::cout<<"Nucleus has decayed into an electron, with an 85.1% chance of further decay"<<std::endl;
          double prob2 = dis(gen);
          if(prob2 < 0.851)
          {
            std::cout<<"Nucleus has undergone a second decay into a photon"<<std::endl;
            Photon p1{0, 0.661, std::vector<std::shared_ptr<Electron>>{}};
            r.photon = std::make_shared<Photon>(p1);
            photons.push_back(p1);
          }
          else 
          {
            Photon p2{0, 0, std::vector<std::shared_ptr<Electron>>{}};
            r.photon = std::make_shared<Photon>(p2);
            photons.push_back(p2);
          }
          r.decayed = true;
          r.photon->print_data();
          return photons;
        }
        else
        {
          std::cout<<"Nucleus has decayed into an electron"<<std::endl;
          r.decayed = true;
          Photon p3{0, 0, std::vector<std::shared_ptr<Electron>>{}};
          r.photon = std::make_shared<Photon>(p3);
          photons.push_back(p3);
          r.photon->print_data();
          return photons;
        }
      }
      else if(r.nucleus_type == "Co") //decided to ignore the electrons here as the energies didnt make sense on blackboard
      {
        double prob = dis(gen);
        Photon p1{0, 1.173, std::vector<std::shared_ptr<Electron>>{}};
        Photon p2{0, 1.333, std::vector<std::shared_ptr<Electron>>{}};
        if(prob<0.9988)
        {
          std::cout<<"Nucleus has decayed into an electron and photon, and will undergo further decay into a photon"<<std::endl;
          r.decayed = true;
          r.photon = std::make_shared<Photon>(p1);
          r.photon->print_data();
          r.photon = std::make_shared<Photon>(p2);
          r.photon->print_data();
          photons.push_back(p1);
          photons.push_back(p2);
          return photons;
          
        } //case1: two photons produced 1 
        else
        {
          std::cout<<"Nucleus has decayed into a photon and an electron"<<std::endl;
          r.decayed = true; 
          r.photon = std::make_shared<Photon>(p2);
          r.photon->print_data();
          photons.push_back(p2);
          return photons;
        } //case2: 1 photon produced
      }
      else
      {
        std::cout<<"Error: invalid nucleus type"<<std::endl;
        return photons; //return empty vector if nucleus type is invalid 
      }

    }
  }

};

#endif