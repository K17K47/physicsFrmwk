#ifndef FORCEGENERATORS_HPP_
#define FORCEGENERATORS_HPP_

#include"particles/pMngr.hpp"
#include"particles/pForceGens.hpp"
#include"aux/math.hpp"

namespace Physics{

   class fgSpring : public pForceGen{
      private:
         unsigned p1;
         unsigned p2;
         real k1;
         real d0;

         Vector3 acceleration(pMngr* particles, real dt, Vector3 velocity);
      public:
         fgSpring(unsigned p1, unsigned p2, real k1, real x0);
         void updateForce(pMngr* particles, real dt);
   };

   class fgLinearDamper : public pForceGen{
      private:
         unsigned p;
         real k;
      public:
         fgLinearDamper(unsigned p, real k);
         void updateForce(pMngr* particles, real dt);
   };

   class fgDrag : public pForceGen{
      private:
         unsigned p;
         real k;
      public:
         fgDrag(unsigned p, real k);
         void updateForce(pMngr* particles, real dt);
   };

};

#endif
