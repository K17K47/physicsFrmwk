#ifndef PWORLD_HPP_
#define PWORLD_HPP_

#include"particles/pMngr.hpp"
//#include"particles/pForceGens.hpp"
//#include"particles/pCollisions.hpp"
//#include"particles/pGenerators.hpp"

namespace Physics{

   class pWorld{
      public:
         Physics::pMngr* particles;
         //Physics::pForceGens* forceGens;
         //Physics::pCollisions* collisions;
         //Physics::pGenerators* generators;
      public:
         pWorld();
         ~pWorld();
         void runPhysics(real dt);
   };

};

#endif
