#include"particles/pForceGens.hpp"
#include"aux/math.hpp"

namespace Physics{
   unsigned pForceGens::add(pForceGen* fg){
      return forceGens.insert(fg);
   }

   void pForceGens::remove(unsigned idx){
      forceGens.erase(idx);
   }

   void pForceGens::clear(){
      forceGens.clear();
   }

   void pForceGens::updateForces(pMngr* particles, real dt){
   // TODO: use a thread pool
      if(!ncpus || (forceGens.size() < ncpus)){
         update(particles, dt, 0, forceGens.size());
      } else {
         unsigned tPerCore = forceGens.size()/ncpus, i;

         for(i=0; i<ncpus-1; i++){
            threads.push_back(std::thread(&pForceGens::update, this, particles, dt, i*tPerCore, (i+1)*tPerCore));
         }

         threads.push_back(std::thread(&pForceGens::update, this, particles, dt, i*tPerCore, forceGens.size()));

         for(i=0; i<ncpus; i++) threads[i].join();

         threads.clear();
      }
   }

   void pForceGens::update(pMngr* particles, real dt, unsigned start, unsigned end){
      for(unsigned i=start; i<end; i++){
         forceGens[i]->updateForce(particles, dt);
      }
   }
};
