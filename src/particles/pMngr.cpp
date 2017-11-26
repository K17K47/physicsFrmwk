#include"particles/pMngr.hpp"

namespace Physics{
   void pMngr::integrate(real dt, unsigned start, unsigned end){
      unsigned i;

      for(i=start;i<end;i++)
         reg.get(i).integrate(dt);
   }

   void pMngr::simulateParticles(real dt){   //TODO: Use a thread pool instead
      if(!ncpus || ( reg.size() < ncpus )){
         integrate(dt, 0, reg.size());
      } else {
         unsigned tPerCore = reg.size()/ncpus, i;

         for(i=0; i<ncpus-1; i++){
            threads.push_back(std::thread(&pMngr::integrate, this, dt, i*tPerCore, (i+1)*tPerCore));
         }

         threads.push_back(std::thread(&pMngr::integrate, this, dt, i*tPerCore, reg.size()));

         for(i=0; i<ncpus; i++) threads[i].join();

         threads.clear();

      }
   }

   unsigned pMngr::newParticle(){
      Particle p;
      return reg.insert(p);
   }

   unsigned pMngr::add(Particle p){
      return reg.insert(p);
   }

   unsigned pMngr::add(Particle *p){
      return reg.insert(*p);
   }

   void pMngr::remove(const unsigned idx){
      reg.erase(idx);
   }

   Particle& pMngr::operator[](const unsigned idx){
      return reg[idx];
   }

   Particle pMngr::operator[](const unsigned idx) const{
      return reg[idx];
   }
};
