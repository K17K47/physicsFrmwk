#ifndef PFORCEGENS_HPP_
#define PFORCEGENS_HPP_

#include"particles/pMngr.hpp"
#include"aux/math.hpp"
#include<thread>

namespace Physics{
   // Base class for "Force Generators", the way of computing forces between
   // particles
   class pForceGen{
      public:
         virtual void updateForce(pMngr* particles, real dt) = 0;
   };

   class pForceGens{
      private:
         // Registry of Force Generators
         std::vector<pForceGen*> forceGens;

         // Registry structure members
         std::vector<unsigned> bReference;
         std::vector<unsigned> indirection;
         std::vector<unsigned> free;
         unsigned dataInsert(pForceGen *fg);
         void dataErase(unsigned idx);

         // Things for multithreading
         unsigned ncpus = std::thread::hardware_concurrency();
         std::vector<std::thread> threads;

         // Compute forces for "particles" particles over a timestep "dt".
         // Runs for Force Gens with indexes between "start" and "end"
         void update(pMngr* particles, real dt, unsigned start, unsigned end);
      public:
         // Methods for managing the Force Generators registry
         unsigned add(pForceGen *fg);
         void remove(unsigned idx);
         void clear();

         // Compute forces for "particles" over a timestep "dt"
         void updateForces(pMngr* particles, real dt);
   };

};

#endif
