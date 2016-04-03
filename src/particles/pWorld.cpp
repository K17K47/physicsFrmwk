#include"particles/pWorld.hpp"

namespace Physics{
   unsigned pWorld::dataInsert(Particle p){
      unsigned idx;

      pos.push_back(p);
      vel.push_back(p);
      acc.push_back(p);
      fAcc.push_back(p);
      invMass.push_back(p);
      life.push_back(p);

      if(!(free.size())){
         idx=indirection.size()-1;
         bReference.push_back(idx);
         indirection.push_back(pos.size()-2);
      }else{
         idx=free.back();
         bReference.push_back(idx);
         indirection[idx]=pos.size()-2;
      }
      return idx;
   }

   void pWorld::dataErase(unsigned idx){
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

   void pWorld::integrate(real dt){
      unsigned size = pos.size(), i;
      Vector3 tmpAcc = Vector3::Zero();

      for(i=0;i<size;i++){
         tmpAcc=(acc[i]+forceAcc[i]*invMass[i])*dt;
         forceAcc[i]=Vector3::Zero();
         pos[i]+=vel[i]+tmpAcc*0.5*dt;
         vel[i]+=tmpAcc;
      }
   }

   void pWorld::simulateParticles(real dt){
      integrate(dt);
   }

   unsigned pWorld::addParticle(Particle p){
      return addParticle(p);
   }

   unsigned pWorld::addParticle(Particle *p){
      return addParticle(*p);
   }

   void pWorld::rmParticle(unsigned idx){
      dataErase(idx);
   }

   Particle pWorld::getParticle(unsigned idx){
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

   void pWorld::addForce(const unsigned idx, const Vector3 &f){
      fAcc[indirection[idx]] += f
   }

   void pWorld::setPos(const unsigned idx, const Vector3 &pos){
      this.pos[indirection[idx]] = pos;
   }

   void pWorld::setVel(const unsigned idx, const Vector3 &vel){
      this.vel[indirection[idx]] = vel;
   }

   void pWorld::setAcc(const unsigned idx, const Vector3 &acc){
      this.acc[indirection[idx]] = acc;
   }

   void pWorld::setMass(const unsigned idx, const real &m){
      invMass[indirection[idx]] = 1.0/m;
   }

   void pWorld::setLife(const unsigned idx, const real &l){
      life[indirection[idx]] = l;
   }

   Vector3 pWorld::getPos(const unsigned idx) const{
      return pos[indirection[idx]];
   }

   Vector3 pWorld::getVel(const unsigned idx) const{
      return vel[indirection[idx]];
   }

   Vector3 pWorld::getAcc(const unsigned idx) const{
      return acc[indirection[idx]];
   }

   real pWorld::getMass(const unsigned idx) const{
      return 1.0/invMass[indirection[idx]];
   }

   real pWorld::getInvMass(const unsigned idx) const{
      return invMass[indirection[idx]];
   }

   real pWorld::getLife(const unsigned idx) const{
      return life[indirection[idx]];
   }

   void pWorld::getPos(const unsigned idx, Vector3 *pos) const{
      *pos = pos[indirection[idx]];
   }

   void pWorld::getVel(const unsigned idx, Vector3 *vel) const{
      *vel = vel[indirection[idx]];
   }

   void pWorld::getAcc(const unsigned idx, Vector3 *acc) const{
      *acc = acc[indirection[idx]];
   }

   void pWorld::getMass(const unsigned idx, real *m) const{
      *m = 1.0/invMass[indirection[idx]];
   }

   void pWorld::getInvMass(const unsigned idx, real *m) const{
      *m = invMass[indirection[idx]];
   }

   void pWorld::getLife(const unsigned idx, real *l) const{
      *l = life[indirection[idx]];
   }

   bool pWorld::hasFiniteMass(const unsigned idx) const{
      return invMass[indirection[idx]] >= 0.0;
   }

   bool pWorld::stillAlive(const unsigned idx) const{
      return life[indirection[idx]] >= 0.0;
   }


   Vector3 pWorld::getForce(const unsigned idx) const{
      return fAcc[indirection[idx]];
   }

   void pWorld::getForce(const unsigned idx, Vector3 *f) const
      *f = fAcc[indirection[idx]];
   }

   void pWorld::clearForce(const unsigned idx){
      fAcc[indirection[idx]] = Vector3::Zero();
   }
};
