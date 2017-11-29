#include"particles/particle.hpp"

namespace Physics{
   void Particle::integrate(real dt){
      std::lock_guard<std::mutex> lock(mtx);
      //Greasy 4th-order Runge-Kutta integrator
      Vector3 tmpAcc = (a + force*invMass)*dt;
      force = Vector3::Zero();

      v += impulse*invMass;
      impulse = Vector3::Zero();

      p += (v + tmpAcc*0.5)*dt;
      v += tmpAcc;

      if(life && life != REAL_MAX) life -= dt;
   }

   void Particle::addForce(const Vector3 &f){
      std::lock_guard<std::mutex> lock(mtx);
      force += f;
   }

   void Particle::addImpulse(const Vector3 &i){
      std::lock_guard<std::mutex> lock(mtx);
      impulse += i;
   }

   void Particle::setPos(const Vector3 &pos){
      std::lock_guard<std::mutex> lock(mtx);
      p = pos;
   }

   void Particle::setVel(const Vector3 &vel){
      std::lock_guard<std::mutex> lock(mtx);
      v = vel;
   }

   void Particle::setAcc(const Vector3 &acc){
      std::lock_guard<std::mutex> lock(mtx);
      a = acc;
   }

   void Particle::setMass(const real &m){
      std::lock_guard<std::mutex> lock(mtx);
      invMass = 1/m;
   }

   void Particle::setLife(const real &l){
      std::lock_guard<std::mutex> lock(mtx);
      life = l;
   }

   Vector3 Particle::getPos() const{
      std::lock_guard<std::mutex> lock(mtx);
      return p;
   }

   Vector3 Particle::getVel() const{
      std::lock_guard<std::mutex> lock(mtx);
      return v;
   }

   Vector3 Particle::getAcc() const{
      std::lock_guard<std::mutex> lock(mtx);
      return a;
   }

   real Particle::getMass() const{
      std::lock_guard<std::mutex> lock(mtx);
      if(!invMass){
         return REAL_MAX;
      }else{
         return 1.0/invMass;
      }
   }

   real Particle::getInvMass() const{
      std::lock_guard<std::mutex> lock(mtx);
      return invMass;
   }

   real Particle::getLife() const{
      std::lock_guard<std::mutex> lock(mtx);
      return life;
   }

   void Particle::getPos(Vector3 *pos) const{
      std::lock_guard<std::mutex> lock(mtx);
      *pos = p;
   }

   void Particle::getVel(Vector3 *vel) const{
      std::lock_guard<std::mutex> lock(mtx);
      *vel = v;
   }

   void Particle::getAcc(Vector3 *acc) const{
      std::lock_guard<std::mutex> lock(mtx);
      *acc = a;
   }

   void Particle::getMass(real *m) const{
      std::lock_guard<std::mutex> lock(mtx);
      *m = 1.0/invMass;
   }

   void Particle::getInvMass(real *m) const{
      std::lock_guard<std::mutex> lock(mtx);
      *m = invMass;
   }

   void Particle::getLife(real *l) const{
      std::lock_guard<std::mutex> lock(mtx);
      *l = life;
   }

   bool Particle::hasFiniteMass() const{
      std::lock_guard<std::mutex> lock(mtx);
      return invMass >= 0.0;
   }

   bool Particle::stillAlive() const{
      std::lock_guard<std::mutex> lock(mtx);
      return life >= 0.0;
   }

   Vector3 Particle::getForce() const{
      std::lock_guard<std::mutex> lock(mtx);
      return force;
   }

   void Particle::getForce(Vector3 *f) const{
      std::lock_guard<std::mutex> lock(mtx);
      *f = force;
   }

   void Particle::clearForce(){
      std::lock_guard<std::mutex> lock(mtx);
      force = Vector3::Zero();
   }

   Vector3 Particle::getImpulse() const{
      std::lock_guard<std::mutex> lock(mtx);
      return impulse;
   }

   void Particle::getImpulse(Vector3 *i) const{
      std::lock_guard<std::mutex> lock(mtx);
      *i = impulse;
   }

   void Particle::clearImpulse(){
      std::lock_guard<std::mutex> lock(mtx);
      impulse = Vector3::Zero();
   }
};
