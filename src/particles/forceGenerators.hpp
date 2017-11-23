#ifndef FORCEGENERATORS_HPP_
#define FORCEGENERATORS_HPP_

#include"particles/pMngr.hpp"
#include"particles/pForceGens.hpp"
#include"aux/math.hpp"

namespace Physics{

   class fgSpring : public pForceGen{
      private:
         // Targeted particles idx
         unsigned p1;
         unsigned p2;

         real k1; // Spring const.
         real d0; // Natural length

         Vector3 force(pMngr* particles, real dt, Vector3 impulse);
      public:
         fgSpring(unsigned p1, unsigned p2, real k1, real x0);
         void updateForce(pMngr* particles, real dt);
   };

   // Linear Drag
   class fgLinearDamper : public pForceGen{
      private:
         unsigned p; // Target particle idx
         real k;  // Drag const.
      public:
         fgLinearDamper(unsigned p, real k);
         void updateForce(pMngr* particles, real dt);
   };

   // Viscous Drag
   class fgDrag : public pForceGen{
      private:
         unsigned p; // Target particle idx
         real k;  // Drag const.
      public:
         fgDrag(unsigned p, real k);
         void updateForce(pMngr* particles, real dt);
   };

   // 1/r^2 force/gravitational force
   class fgGravity : public pForceGen{
      private:
         unsigned p1;
         unsigned p2;
         real k1;

         Vector3 force(pMngr* particles, real dt, Vector3 velocity);
      public:
         fgGravity(unsigned p1, unsigned p2, real k1);
         void updateForce(pMngr* particles, real dt);
   };
};

#endif
