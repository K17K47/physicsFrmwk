#include"particles/pForceGens.hpp"
#include"aux/math.hpp"

namespace Physics{

   unsigned pForceGens::dataInsert(pForceGen* fg){
      unsigned idx = 0;
      forceGens.push_back(fg);

      if(!(free.size())){
         idx=indirection.size();
         bReference.push_back(idx);
         indirection.push_back(forceGens.size()-1);
      }else{
         idx=free.back();
         bReference.push_back(idx);
         indirection[idx]=forceGens.size()-1;
      }

      return idx;
   }

   void pForceGens::dataErase(unsigned idx){
      unsigned indir = indirection[idx];

      forceGens[indir] = forceGens.back();

      bReference[indir] = bReference.back();
      indirection[bReference.back()] = indirection[idx];

      free.push_back(idx);

      bReference.pop_back();

      forceGens.pop_back();
   }

   unsigned pForceGens::add(pForceGen* fg){
      return dataInsert(fg);
   }

   void pForceGens::remove(unsigned idx){
      dataErase(idx);
   }

   void pForceGens::clear(){
      forceGens.clear();
      bReference.clear();
      indirection.clear();
      free.clear();
   }

   void pForceGens::updateForces(pMngr* particles, real dt){
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
