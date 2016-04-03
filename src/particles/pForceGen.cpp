#include"particles/pForceGen.hpp"

namespace Physics{
   unsigned pForceGenRegistry::dataInsert(pForceGen *fg, unsigned pOne, unsigned pTwo){
      unsigned idx;

      forceGens.push_back(fg);
      pOnes.push_back(pOne);
      pTwos.push_back(pTwo);

      if(!(free.size())){
         idx=indirection.size()-1;
         bReference.push_back(idx);
         indirection.push_back(forceGens.size()-2);
      }else{
         idx=free.back();
         bReference.push_back(idx);
         indirection[idx]=forceGens.size()-2;
      }
      return idx;
   }

   void pForceGenRegistry::dataErase(unsigned idx){
      unsigned indir = indirection[idx];

      forceGens[indir] = forceGens.back();
      pOnes[indir] = pOnes.back();
      pTwos[indir] = pTwos.back();

      bReference[indir] = bReference.back();
      indirection[bReference.back()] = indirection[idx];

      free.push_back(idx);

      bReference.pop_back();
      forceGens.pop_back();
      pOnes.pop_back();
      pTwos.pop_back();
   }

   void pForceGenRegistry::add(pForceGen *fg, unsigned pOne, unsigned pTwo){
      dataInsert(fg, pOne, pTwo);
   }

   void pForceGenRegistry::remove(unsigned idx){
      dataErase(idx);
   }

   void pForceGenRegistry::clear(){
      forceGens.clear();
      pOnes.clear();
      pTwos.clear();

      bReference.clear();
      indirection.clear();
      free.clear();
   }

   void pForceGenRegistry::updateForces(real dt){
      for(unsigned i=0; i<forceGens.size(); i++){
         *(forceGens[i])->updateForce(targetWorld, dt, pOnes[i], pTwos[i]); 
      } 
   }

   void setWorld(pWorld *pW){
      targetWorld = pW;
   }
};
