#include"particles/forceGenerators.hpp"

namespace Physics{

   fgSpring::fgSpring(unsigned p1, unsigned p2, real k1, real x0){
      this->p1 = p1;
      this->p2 = p2;
      this->k1 = k1;
      this->d0 = x0;
   }

   void fgSpring::updateForce(pMngr* particles, real dt){
      Vector3 c1 = acceleration(particles, 0.0, Vector3::Zero());
      Vector3 c2 = acceleration(particles, 0.5*dt, 0.5*dt*c1);
      Vector3 c3 = acceleration(particles, 0.5*dt, 0.5*dt*c2);
      Vector3 c4 = acceleration(particles, dt, dt*c3);

      Vector3 v = (1.0/6.0)*dt*(c1+c4+2*(c2+c3));

      particles->setVel(p1, particles->getVel(p1)+v);
      particles->setVel(p2, particles->getVel(p2)-v);

   }

   Vector3 fgSpring::acceleration(pMngr* particles, real dt, Vector3 velocity){
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
      f = -k*f;
      particles->addForce(p, f);
   }

   fgDrag::fgDrag(unsigned p, real k){
      this->p = p;
      this->k = k;
   }

   void fgDrag::updateForce(pMngr* particles, real dt){
      Vector3 f = particles->getVel(p);
      real d = f.norm();
      f = -k*d*f;
      particles->addForce(p, f);
   }
};
