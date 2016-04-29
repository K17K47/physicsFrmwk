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
      for(unsigned i = 0; i<forceGens.size(); i++){
         forceGens[i]->updateForce(particles, dt);
      }
   }

};
