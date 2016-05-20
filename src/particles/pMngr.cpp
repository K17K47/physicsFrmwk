#include"particles/pMngr.hpp"

namespace Physics{
   unsigned pMngr::dataInsert(Particle p){
      unsigned idx;

      std::lock_guard<std::mutex> guard(mtx);

      pos.push_back(p.getPos());
      vel.push_back(p.getVel());
      acc.push_back(p.getAcc());
      fAcc.push_back(p.getForce());
      iAcc.push_back(p.getImpulse());
      invMass.push_back(p.getInvMass());
      life.push_back(p.getLife());

      if(!(free.size())){
         idx=indirection.size();
         bReference.push_back(idx);
         indirection.push_back(pos.size()-1);
      }else{
         idx=free.back();
         bReference.push_back(idx);
         indirection[idx]=pos.size()-1;
      }

      return idx;
   }

   void pMngr::dataErase(unsigned idx){
      unsigned indir = indirection[idx];

      std::lock_guard<std::mutex> guard(mtx);

      pos[indir] = pos.back();
      vel[indir] = vel.back();
      acc[indir] = acc.back();
      fAcc[indir] = fAcc.back();
      iAcc[indir] = iAcc.back();
      invMass[indir] = invMass.back();
      life[indir] = life.back();

      bReference[indir] = bReference.back();
      indirection[bReference.back()] = indirection[idx];

      free.push_back(idx);

      bReference.pop_back();
      pos.pop_back();
      vel.pop_back();
      acc.pop_back();
      fAcc.pop_back();
      iAcc.pop_back();
      invMass.pop_back();
      life.pop_back();
   }

   void pMngr::integrate(real dt, unsigned start, unsigned end){
      unsigned i;
      Vector3 tmpAcc = Vector3::Zero();

      for(i=start;i<end;i++){
         tmpAcc=(acc[i]+fAcc[i]*invMass[i])*dt;
         fAcc[i]=Vector3::Zero();
         vel[i]+=iAcc[i]*invMass[i];
         iAcc[i]=Vector3::Zero();
         pos[i]+=(vel[i]+tmpAcc*0.5)*dt;
         vel[i]+=tmpAcc;
         if(life[i]) life[i]-=dt;
      }
   }

   void pMngr::simulateParticles(real dt){
      if(!ncpus || ( pos.size() < ncpus )){
         integrate(dt, 0, pos.size());
      } else {
         unsigned tPerCore = pos.size()/ncpus, i;

         for(i=0; i<ncpus-1; i++){
            threads.push_back(std::thread(&pMngr::integrate, this, dt, i*tPerCore, (i+1)*tPerCore));
         }

         threads.push_back(std::thread(&pMngr::integrate, this, dt, i*tPerCore, pos.size()));

         for(i=0; i<ncpus; i++) threads[i].join();

         threads.clear();

      }
   }

   unsigned pMngr::newParticle(){
      Particle p;
      return dataInsert(p);
   }

   unsigned pMngr::add(Particle p){
      return dataInsert(p);
   }

   unsigned pMngr::add(Particle *p){
      return add(*p);
   }

   void pMngr::remove(unsigned idx){
      dataErase(idx);
   }

   Particle pMngr::get(unsigned idx){
      Particle p;

      std::lock_guard<std::mutex> guard(mtx);

      p.setPos(pos[indirection[idx]]);
      p.setVel(vel[indirection[idx]]);
      p.setAcc(acc[indirection[idx]]);
      p.clearForce();
      p.clearImpulse();
      p.addForce(fAcc[indirection[idx]]);
      p.setLife(life[indirection[idx]]);
      p.setMass(1.0/invMass[indirection[idx]]);

      return p;
   }

   void pMngr::addForce(const unsigned idx, const Vector3 &f){
      std::lock_guard<std::mutex> guard(mtx);
      fAcc[indirection[idx]] += f;
   }

   void pMngr::addImpulse(const unsigned idx, const Vector3 &i){
      std::lock_guard<std::mutex> guard(mtx);
      iAcc[indirection[idx]] += i;
   }

   void pMngr::setPos(const unsigned idx, const Vector3 &position){
      std::lock_guard<std::mutex> guard(mtx);
      pos[indirection[idx]] = position;
   }

   void pMngr::setVel(const unsigned idx, const Vector3 &vel){
      std::lock_guard<std::mutex> guard(mtx);
      this->vel[indirection[idx]] = vel;
   }

   void pMngr::setAcc(const unsigned idx, const Vector3 &acc){
      std::lock_guard<std::mutex> guard(mtx);
      this->acc[indirection[idx]] = acc;
   }

   void pMngr::setMass(const unsigned idx, const real &m){
      std::lock_guard<std::mutex> guard(mtx);
      invMass[indirection[idx]] = 1.0/m;
   }

   void pMngr::setLife(const unsigned idx, const real &l){
      std::lock_guard<std::mutex> guard(mtx);
      life[indirection[idx]] = l;
   }

   Vector3 pMngr::getPos(const unsigned idx) const{
      return pos[indirection[idx]];
   }

   Vector3 pMngr::getVel(const unsigned idx) const{
      return vel[indirection[idx]];
   }

   Vector3 pMngr::getAcc(const unsigned idx) const{
      return acc[indirection[idx]];
   }

   real pMngr::getMass(const unsigned idx) const{
      return 1.0/invMass[indirection[idx]];
   }

   real pMngr::getInvMass(const unsigned idx) const{
      return invMass[indirection[idx]];
   }

   real pMngr::getLife(const unsigned idx) const{
      return life[indirection[idx]];
   }

   void pMngr::getPos(const unsigned idx, Vector3 *pos) const{
      *pos = pos[indirection[idx]];
   }

   void pMngr::getVel(const unsigned idx, Vector3 *vel) const{
      *vel = vel[indirection[idx]];
   }

   void pMngr::getAcc(const unsigned idx, Vector3 *acc) const{
      *acc = acc[indirection[idx]];
   }

   void pMngr::getMass(const unsigned idx, real *m) const{
      *m = 1.0/invMass[indirection[idx]];
   }

   void pMngr::getInvMass(const unsigned idx, real *m) const{
      *m = invMass[indirection[idx]];
   }

   void pMngr::getLife(const unsigned idx, real *l) const{
      *l = life[indirection[idx]];
   }

   bool pMngr::hasFiniteMass(const unsigned idx) const{
      return invMass[indirection[idx]] >= 0.0;
   }

   bool pMngr::stillAlive(const unsigned idx) const{
      return life[indirection[idx]] >= 0.0;
   }


   Vector3 pMngr::getForce(const unsigned idx) const{
      return fAcc[indirection[idx]];
   }

   void pMngr::getForce(const unsigned idx, Vector3 *f) const{
      *f = fAcc[indirection[idx]];
   }

   void pMngr::clearForce(const unsigned idx){
      fAcc[indirection[idx]] = Vector3::Zero();
   }

   Vector3 pMngr::getImpulse(const unsigned idx) const{
      return iAcc[indirection[idx]];
   }

   void pMngr::getImpulse(const unsigned idx, Vector3 *i) const{
      *i = iAcc[indirection[idx]];
   }

   void pMngr::clearImpulse(const unsigned idx){
      iAcc[indirection[idx]] = Vector3::Zero();
   }
};
