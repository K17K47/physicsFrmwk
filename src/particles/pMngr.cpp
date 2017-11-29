#include"particles/pMngr.hpp"

namespace Physics{
   void pMngr::integrate(real dt, unsigned start, unsigned end){
      unsigned i;

      for(i=start;i<end;i++)
         reg.get(i).integrate(dt);
   }

   void pMngr::simulateParticles(real dt){   //TODO: Use a thread pool instead
      unsigned ncpus = std::thread::hardware_concurrency();
      unsigned nPart = reg.size();

      if(!ncpus || ( nPart < ncpus )){
         integrate(dt, 0, nPart);
      } else {
         unsigned tPerCore = nPart/ncpus, i;

         for(i=0;i<ncpus;i++)
            pool.enqueue([dt,i,tPerCore,this](){this->integrate(dt,i*tPerCore,(i+1)*tPerCore);});

         pool.enqueue([dt,ncpus,tPerCore,nPart,this](){this->integrate(dt,ncpus*tPerCore,nPart);});

         pool.waitFinish();
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
