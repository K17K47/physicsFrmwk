#ifndef PFORCEGENS_HPP_
#define PFORCEGENS_HPP_

#include"particles/pWorld.hpp"
#include"aux/math.h"

namespace Physics{

   class pForceGens{
      private:
         std::vector<pForceGen*> forceGens;

         std::vector<unsigned> bReference;
         std::vector<unsigned> indirection;
         std::vector<unsigned> free;

         unsigned dataInsert(pForceGen *fg);
         void dataErase(unsigned idx);
      public:
         unsigned add(pForceGen *fg);
         void remove(unsigned idx);

         void clear();

         void updateForces(pMngr* particles, real dt);
   };

};

#endif
