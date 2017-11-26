#include"particles/forceGenerators.hpp"

namespace Physics{

   fgSpring::fgSpring(unsigned p1, unsigned p2, real k1, real x0){
      this->p1 = p1;
      this->p2 = p2;
      this->k1 = k1;
      this->d0 = x0;
   }

   void fgSpring::updateForce(pMngr* particles, real dt){
      Vector3 c1 = force(particles, 0.0, Vector3::Zero());
      Vector3 c2 = force(particles, 0.5*dt, 0.5*dt*c1);
      Vector3 c3 = force(particles, 0.5*dt, 0.5*dt*c2);
      Vector3 c4 = force(particles, dt, dt*c3);

      Vector3 i = (1.0/6.0)*dt*(c1+c4+2*(c2+c3));

      particles[p1].addImpulse(i);
      particles[p2].addImpulse(-i);
   }

   Vector3 fgSpring::force(pMngr* particles, real dt, Vector3 impulse){
      Vector3 vd = particles[p2].getPos - particles[p1].getPos();
      real d = vd.norm();
      return ((k1*(d-d0))/d)*vd;
   }


   fgLinearDamper::fgLinearDamper(unsigned p, real k){
      this->p = p;
      this->k = k;
   }

   void fgLinearDamper::updateForce(pMngr* particles, real dt){
      Vector3 f = particles[p].getVel();
      f *= -(k*particles[p].getMass());
      particles[p].addForce(f);
   }

   fgDrag::fgDrag(unsigned p, real k){
      this->p = p;
      this->k = k;
   }

   void fgDrag::updateForce(pMngr* particles, real dt){
      Vector3 f = particles[p].getVel();
      if(f.norm()){
         f.normalize();
         f *= -(k*particles[p].getMass());
         particles[p].addForce(f);
      }
   }

   fgGravity::fgGravity(unsigned p1, unsigned p2, real k1){
      this->p1 = p1;
      this->p2 = p2;
      this->k1 = k1;
   }

   void fgGravity::updateForce(pMngr* particles, real dt){
      Vector3 c1 = force(particles, 0.0, Vector3::Zero());
      Vector3 c2 = force(particles, 0.5*dt, 0.5*dt*c1);
      Vector3 c3 = force(particles, 0.5*dt, 0.5*dt*c2);
      Vector3 c4 = force(particles, dt, dt*c3);

      Vector3 i = (1.0/6.0)*dt*(c1+c4+2*(c2+c3));

      particles[p1].addImpulse(i);
      particles[p2].addImpulse(-i);
   }

   Vector3 fgGravity::force(pMngr* particles, real dt, Vector3 velocity){
      Vector3 vd = particles[p2].getPos() - particles[p1].getPos();
      real d = vd.norm();
      return (k1/(d*d*d))*particles[p1].getMass()*particles[p2].getMass()*vd;
   }
};

