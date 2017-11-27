#ifndef PFORCEGENS_HPP_
#define PFORCEGENS_HPP_

#include"particles/pMngr.hpp"
#include"aux/math.hpp"
#include"aux/slotmap.hpp"
#include"aux/ThreadPool.h"

namespace Physics{
   // Base class for "Force Generators", the way of computing forces between
   // particles
   class pForceGen{
      public:
         virtual void updateForce(pMngr* particles, real dt) = 0;
   };

   /*
    * Force Generators should inherit the class pForceGen as public, and
    * implement force and/or impulse calculation inside updateForce,
    * overriding it.
    * Example:
    *
    * class genericForceGen : public pForceGen{
    *    private:
    *       unsigned particleIdx;
    *       real springConst;
    *    public:
    *       void updateForce(pMngr* particles, real dt);
    * };
    *
    * void genericDragForceGen::updateForce(){
    *    Vector3 f = particles->getVel(particleIdx);
    *    f *= -(springConst * particles->getMass(particleIdx));
    *    particles->addForce(particleIdx, f);
    * }
    *
    */

   class pForceGens{
      private:
         // Registry of Force Generators
         slotMap<pForceGen*> forceGens;

         // Things for multithreading
         ThreadPool pool;

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
