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
      unsigned ncpus = std::thread::hardware_concurrency();
      unsigned nFG = forceGens.size();

      if(!ncpus || (nFG < ncpus)){
         update(particles, dt, 0, nFG);
      } else {
         unsigned tPerCore = nFG/ncpus, i;

         for(i=0; i<ncpus-1; i++)
            pool.enqueue([particles,dt,i,tPerCore,this]{
               this->update(particles, dt,i*tPerCore,(i+1)*tPerCore);
            });

         pool.enqueue([particles,dt,i,tPerCore,nFG,this]{
               this->update(particles, dt,i*tPerCore, nFG);
         });

         pool.waitFinish();
      }
   }

   void pForceGens::update(pMngr* particles, real dt, unsigned start, unsigned end){
      for(unsigned i=start; i<end; i++){
         forceGens.get(i)->updateForce(particles, dt);
      }
   }
};
