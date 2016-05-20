#ifndef PFORCEGENS_HPP_
#define PFORCEGENS_HPP_

#include"particles/pMngr.hpp"
#include"aux/math.hpp"
#include<thread>

namespace Physics{
   class pForceGen{
      public:
         virtual void updateForce(pMngr* particles, real dt) = 0;
   };

   class pForceGens{
      private:
         std::vector<pForceGen*> forceGens;

         std::vector<unsigned> bReference;
         std::vector<unsigned> indirection;
         std::vector<unsigned> free;

         unsigned dataInsert(pForceGen *fg);
         void dataErase(unsigned idx);

         unsigned ncpus = std::thread::hardware_concurrency();

         std::vector<std::thread> threads;

         void update(pMngr* particles, real dt, unsigned start, unsigned end);
      public:
         unsigned add(pForceGen *fg);
         void remove(unsigned idx);

         void clear();

         void updateForces(pMngr* particles, real dt);
   };

};

#endif
