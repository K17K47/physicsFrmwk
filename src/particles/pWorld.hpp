/*
 * Particles World Header
 */

#ifndef PWORLD_HPP_
#define PWORLD_HPP_

#include"particles/pMngr.hpp"
#include"particles/pForceGens.hpp"
//#include"particles/pCollisions.hpp"
//#include"particles/pGenerators.hpp"

namespace Physics{

   class pWorld{
      public:
         // Object manager instances
         pMngr* particles;
         pForceGens* forceGens;
         //Physics::pCollisions* collisions;
         //Physics::pGenerators* generators;
      public:
         pWorld();
         ~pWorld();

         // Run manager instances over a timestep "dt"
         void runPhysics(real dt);
   };

};

#endif
