#include"particles/pWorld.hpp"
#include"aux/math.hpp"

namespace Physics{
   pWorld::pWorld(){
      particles = new pMngr;
      //forceGens = new pForceGens;
      //collisions = new pCollisions;
      //generators = new pGenerators;
   }

   pWorld::~pWorld(){
      delete particles;
      //delete forceGens;
      //delete collisions;
      //delete generators;
   }

   void pWorld::runPhysics(real dt){
      //generators->runGenerators(particles, dt);
      //collisions->resolveCollisions(particles, dt);
      //forceGens->updateForces(particles, dt);
      particles->simulateParticles(dt);
   }
};
