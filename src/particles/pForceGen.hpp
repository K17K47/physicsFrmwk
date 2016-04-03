#ifndef PFORCEGEN_HPP_
#define PFORCEGEN_HPP_

#include"particles/pWorld.hpp"

namespace Physics{

   class pForceGen{
      public:
         virtual void updateForce(pWorld *pW, real dt, unsigned pOne, unsigned pTwo = 0) = 0;
   };

   class pForceGenRegistry{
      private:
         std::vector<*pForceGen> forceGens;
         std::vector<unsigned> pOnes;
         std::vector<unsigned> pTwos;

         std::vector<unsigned> bReference;
         std::vector<unsigned> indirection;
         std::vector<unsigned> free;

         pWorld *targetWorld;

         unsigned dataInsert(pForceGen *fg, unsigned pOne, unsigned pTwo);
         void dataErase(unsigned idx);
      public:
         void add(pForceGen *fg, unsigned pOne, unsigned pTwo = 0);
         void remove(unsigned idx);

         void clear();

         void updateForces(real dt);
         void setWorld(pWorld *pW);
   };

};

#endif
