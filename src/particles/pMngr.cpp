#include"particles/pMngr.hpp"
#include<iostream>

namespace Physics{
   unsigned pMngr::dataInsert(Particle p){
      unsigned idx;

      pos.push_back(p.getPos());
      vel.push_back(p.getVel());
      acc.push_back(p.getAcc());
      fAcc.push_back(p.getForce());
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

      pos[indir] = pos.back();
      vel[indir] = vel.back();
      acc[indir] = acc.back();
      fAcc[indir] = fAcc.back();
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
      invMass.pop_back();
      life.pop_back();
   }

   void pMngr::integrate(real dt){
      unsigned size = pos.size(), i;
      Vector3 tmpAcc = Vector3::Zero();

      for(i=0;i<size;i++){
         tmpAcc=(acc[i]+fAcc[i]*invMass[i])*dt;
         fAcc[i]=Vector3::Zero();
         pos[i]+=vel[i]+tmpAcc*0.5*dt;
         vel[i]+=tmpAcc;
         life[i]-=dt;
      }
   }

   void pMngr::simulateParticles(real dt){
      integrate(dt);
   }

   unsigned pMngr::newParticle(){
      Particle p;
      return dataInsert(p);
   }

   unsigned pMngr::add(Particle p){
      return dataInsert(p);
   }

   unsigned pMngr::add(Particle *p){
      return addParticle(*p);
   }

   void pMngr::remove(unsigned idx){
      dataErase(idx);
   }

   Particle pMngr::get(unsigned idx){
      Particle p;

      p.setPos(pos[indirection[idx]]);
      p.setVel(vel[indirection[idx]]);
      p.setAcc(acc[indirection[idx]]);
      p.clearForce();
      p.addForce(fAcc[indirection[idx]]);
      p.setLife(life[indirection[idx]]);
      p.setMass(1.0/invMass[indirection[idx]]);

      return p;
   }

   void pMngr::addForce(const unsigned idx, const Vector3 &f){
      fAcc[indirection[idx]] += f;
   }

   void pMngr::setPos(const unsigned idx, const Vector3 &position){
      pos[indirection[idx]] = position;
   }

   void pMngr::setVel(const unsigned idx, const Vector3 &vel){
      this->vel[indirection[idx]] = vel;
   }

   void pMngr::setAcc(const unsigned idx, const Vector3 &acc){
      this->acc[indirection[idx]] = acc;
   }

   void pMngr::setMass(const unsigned idx, const real &m){
      invMass[indirection[idx]] = 1.0/m;
   }

   void pMngr::setLife(const unsigned idx, const real &l){
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
};
