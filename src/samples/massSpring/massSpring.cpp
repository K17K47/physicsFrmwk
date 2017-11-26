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
      *(world.particles)[pIdx[i]].setPos(Vector3(i, 0.0, 0.0));
      *(world.particles)[pIdx[i]].setVel(Vector3(0.0, 0.0, 0.0));
      *(world.particles)[pIdx[i]].setAcc(Vector3(0.0, 0.0, 0.0));
      *(world.particles)[pIdx[i]].setMass(10.0);
      *(world.particles)[pIdx[i]].clearForce();
      *(world.particles)[pIdx[i]].clearImpulse();
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
         if(*(world.particles)[pIdx[i]].stillAlive()){
            Vector3 pos = *(world.particles)[pIdx[i]].getPos();
            std::cout<<"\t"<<pos[0];
         }else{
            std::cout<<"Particula "<<i<<" died"<<std::endl;
         }
      }
      std::cout<<"\t"<<(*(world.particles)[pIdx[0]].getPos()-*(world.particles)[pIdx[1]].getPos()).norm()<<std::endl;

      world.runPhysics(DELTAT);
      t+=DELTAT;
   }

   delete spring;
   delete damper;
   delete drag;

   return 0;
}
