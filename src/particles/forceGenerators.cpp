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

      particles->addImpulse(p1, i);
      particles->addImpulse(p2, -i);
   }

   Vector3 fgSpring::force(pMngr* particles, real dt, Vector3 impulse){
      real d = (particles->getPos(p2) - particles->getPos(p1)).norm();
      return ((k1*(d-d0))/d)*(particles->getPos(p2) - particles->getPos(p1));
   }


   fgLinearDamper::fgLinearDamper(unsigned p, real k){
      this->p = p;
      this->k = k;
   }

   void fgLinearDamper::updateForce(pMngr* particles, real dt){
      Vector3 f = particles->getVel(p);
      real d = f.norm();
      f *= -(k*particles->getMass(p));
      particles->addForce(p, f);
   }

   fgDrag::fgDrag(unsigned p, real k){
      this->p = p;
      this->k = k;
   }

   void fgDrag::updateForce(pMngr* particles, real dt){
      Vector3 f = particles->getVel(p);
      //real d = f.norm();
      if(f.norm()){
         f.normalize();
         f *= -(k*particles->getMass(p));
         particles->addForce(p, f);
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

      //particles->setVel(p1, particles->getVel(p1)+v);
      //particles->setVel(p2, particles->getVel(p2)-v);

      particles->addImpulse(p1, i);
      particles->addImpulse(p2, -i);
   }

   Vector3 fgGravity::force(pMngr* particles, real dt, Vector3 velocity){
      real d = (particles->getPos(p2) - particles->getPos(p1)).norm();
      return (k1/(d*d*d))*particles->getMass(p1)*particles->getMass(p2)*(particles->getPos(p2) - particles->getPos(p1));
   }
};

