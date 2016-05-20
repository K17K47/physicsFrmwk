#include<iostream>
#include"physics.hpp"
#include"aux/math.hpp"
#include"particles/forceGenerators.hpp"

#define TMAX   20.0
#define DELTAT 1e-4

int main(){
   Physics::pWorld world;
   unsigned pIdx[2] = {};

   for(int i=0; i<2; i++){
      pIdx[i] = world.particles->newParticle();
      world.particles->setPos(pIdx[i], Vector3(i, 0.0, 0.0));
      world.particles->setVel(pIdx[i], Vector3(0.0, 0.0, 0.0));
      world.particles->setAcc(pIdx[i], Vector3(0.0, 0.0, 0.0));
      world.particles->setMass(pIdx[i], 10.0);
      world.particles->clearForce(pIdx[i]);
      world.particles->clearImpulse(pIdx[i]);
   }

   Physics::pForceGen* spring = new Physics::fgSpring(pIdx[0], pIdx[1], 20.0, 0.5);
   Physics::pForceGen* damper = new Physics::fgLinearDamper(pIdx[0], 0.01);
   Physics::pForceGen* drag = new Physics::fgDrag(pIdx[1], 0.01);

   world.forceGens->add(spring);
   world.forceGens->add(damper);
   world.forceGens->add(drag);

   double t = 0.0;
   while(t < TMAX){
      std::cout<<t;
      for(int i=0; i<2; i++){
         if(world.particles->stillAlive(pIdx[i])){
            Vector3 pos = world.particles->getPos(pIdx[i]);
            std::cout<<"\t"<<pos[0];
         }else{
            std::cout<<"Particula "<<i<<" died"<<std::endl;
         }
      }
      std::cout<<"\t"<<(world.particles->getPos(pIdx[0])-world.particles->getPos(pIdx[1])).norm()<<std::endl;

      world.runPhysics(DELTAT);
      t+=DELTAT;
   }

   delete spring;
   delete damper;
   delete drag;

   return 0;
}
