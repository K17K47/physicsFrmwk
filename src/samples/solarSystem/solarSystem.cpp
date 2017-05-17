#include<iostream>
#include"physics.hpp"
#include"aux/math.hpp"
/*
 * Simulação simplificada do Sistema Solar
*/

#define NOBJ 13      //Número de objetos inclusos na simulacao
#define TMAX 10957.5 //Tempo final da simulacao: +30 anos
#define DELTAT 1e-3  //Passo da simulacao: 1x10^-3 dia

int main(){
   Physics::pWorld world;
   unsigned pIdx[NOBJ] = {};
   Physics::pForceGen* gravityFGs[NOBJ*(NOBJ-1)/2];

   for(int i=0; i<NOBJ; i++){
      pIdx[i] = world.particles->newParticle();
      world.particles->clearForce(pIdx[i]);
      world.particles->clearImpulse(pIdx[i]);
   }

   /*
    * Sun
    *
    * Massa: 1.98855x10^30 Kg
    *
    */
   world.particles->setPos(pIdx[0], Vector3::Zero());
   world.particles->setVel(pIdx[0], Vector3::Zero());
   world.particles->setAcc(pIdx[0], Vector3::Zero());
   world.particles->setMass(pIdx[0], 1.98855e30);

   /*
    * Mercury
    *
    * Periélio: 46.0012x10^6 Km
    * Velocidade no Periélio: 58.98 Km/s
    * Massa: 3.3011x10^23 Kg
    * Inclinação: 7°
    *
    */
   world.particles->setPos(pIdx[1], Vector3(45.65831403e6, 0.0, 5.60613604e6));
   world.particles->setVel(pIdx[1], Vector3(0.0, -5095872, 0.0));
   world.particles->setAcc(pIdx[1], Vector3::Zero());
   world.particles->setMass(pIdx[1], 3.3011e23);

   /*
    * Venus
    *
    * Periélio: 107.48x10^6 Km
    * Velocidade no Periélio: 35.26 Km/s
    * Massa: 4.8675x10^24 Kg
    * Inclinação: 3.39°
    *
    */
   world.particles->setPos(pIdx[2], Vector3(107.2919276e6, 0.0, 6.355523155e6));
   world.particles->setVel(pIdx[2], Vector3(0.0, -3046464, 0.0));
   world.particles->setAcc(pIdx[2], Vector3::Zero());
   world.particles->setMass(pIdx[2], 4.8675e24);

   /*
    * Earth
    *
    * Periélio: 147.1x10^6 Km
    * Velocidade no Periélio: 30.29 Km/s
    * Massa: 5.97237x10^24 Kg
    * Inclinação: 0°
    *
    */
   world.particles->setPos(pIdx[3], Vector3(147.1e6, 0.0, 0.0));
   world.particles->setVel(pIdx[3], Vector3(0.0, -2617056, 0.0));
   world.particles->setAcc(pIdx[3], Vector3::Zero());
   world.particles->setMass(pIdx[3], 5.97237e24);

   /*
    * Mars
    *
    * Periélio: 206.62x10^6 Km
    * Velocidade no Periélio: 26.5 Km/s
    * Massa: 6.4171x10^23 Kg
    * Inclinação: 1.85°
    *
    */
   world.particles->setPos(pIdx[4], Vector3(206.5123032e6, 0.0, 6.67030954e6));
   world.particles->setVel(pIdx[4], Vector3(0.0, -2289600, 0.0));
   world.particles->setAcc(pIdx[4], Vector3::Zero());
   world.particles->setMass(pIdx[4], 6.4171e23);

   /*
    * Jupiter
    *
    * Periélio: 740.52x10^6 Km
    * Velocidade no Periélio: 13.72 Km/s
    * Massa: 1.89819x10^25 Kg
    * Inclinação: 1.304°
    *
    */
   world.particles->setPos(pIdx[5], Vector3(740.3282224e6, 0.0, 16.85210896e6));
   world.particles->setVel(pIdx[5], Vector3(0.0, -1185408, 0.0));
   world.particles->setAcc(pIdx[5], Vector3::Zero());
   world.particles->setMass(pIdx[5], 1.89819e25);

   /*
    * Saturn
    *
    * Periélio: 1.35255x10^9 Km
    * Velocidade no Periélio: 10.18 Km/s
    * Massa: 568.24x10^24 Kg
    * Inclinação: 2.485°
    *
    */
   world.particles->setPos(pIdx[6], Vector3(1.351278071e9, 0.0, 5.864364e7));
   world.particles->setVel(pIdx[6], Vector3(0.0, -879552, 0.0));
   world.particles->setAcc(pIdx[6], Vector3::Zero());
   world.particles->setMass(pIdx[6], 568.34e24);

   /*
    * Uranus
    *
    * Periélio: 2.7413x10^9 Km
    * Velocidade no Periélio: 7.11 Km/s
    * Massa: 86.813x10^24 Kg
    * Inclinação: 0.772°
    *
    */
   world.particles->setPos(pIdx[7], Vector3(2.741051166e9, 0.0, 3.6934999e7));
   world.particles->setVel(pIdx[7], Vector3(0.0, -614304, 0.0));
   world.particles->setAcc(pIdx[7], Vector3::Zero());
   world.particles->setMass(pIdx[7], 86.813e24);

   /*
    * Neptune
    *
    * Periélio: 4.44445x10^9 Km
    * Velocidade no Periélio: 5.5 Km/s
    * Massa: 102.413x10^24 Kg
    * Inclinação: 1.769°
    *
    */
   world.particles->setPos(pIdx[8], Vector3(4.442331815e9, 0.0, 1.37200035e8));
   world.particles->setVel(pIdx[8], Vector3(0.0, -475200, 0.0));
   world.particles->setAcc(pIdx[8], Vector3::Zero());
   world.particles->setMass(pIdx[8], 102.413e24);

   /*
    * Pluto
    *
    * Periélio: 4.43682x10^9 Km
    * Velocidade no Periélio: 6.1 Km/s
    * Massa: 6.97x10^23 Kg
    * Inclinação: 17.16°
    *
    */
   world.particles->setPos(pIdx[9], Vector3(4.239313061e9, 0.0, 1.309044111e9));
   world.particles->setVel(pIdx[9], Vector3(0.0, -527040, 0.0));
   world.particles->setAcc(pIdx[9], Vector3::Zero());
   world.particles->setMass(pIdx[9], 6.97e23);

   /*
    * Moon
    *
    * Pos. Inicial: 147.4633x10^6 Km
    * Vel. Inicial: 31.366 Km/s
    * Massa: 7.346x10^22 Kg
    * Inclinação: 5.145°
    *
    */
   world.particles->setPos(pIdx[10], Vector3(146.8691616e6, 0.0, 13.2240012e6));
   world.particles->setVel(pIdx[10], Vector3(0.0, 2710022.4, 0.0));
   world.particles->setAcc(pIdx[10], Vector3::Zero());
   world.particles->setMass(pIdx[10], 7.346e22);

   /*
    * Ceres
    *
    * Periélio: 382.62x10^6 Km
    * Velocidade no Periélio: 19.318 Km/s
    * Massa: 9.393x10^20 Kg
    * Inclinação: 10.593°
    *
    */
   world.particles->setPos(pIdx[11], Vector3(376.0993194e6, 0.0, 70.3375171e6));
   world.particles->setVel(pIdx[11], Vector3(0.0, -1669161.29, 0.0));
   world.particles->setAcc(pIdx[11], Vector3::Zero());
   world.particles->setMass(pIdx[11], 9.393e20);

   /*
    * Halley Comet
    * Periélio: 87.6656x10^6 Km
    * Velocidade no Periélio: 54 Km/s
    * Massa: 2.2x10^14 Kg
    * Inclinação: 162.3°
    *
    */
   world.particles->setPos(pIdx[12], Vector3(-83.51564035e6, 0.0, 26.65324071e6));
   world.particles->setVel(pIdx[12], Vector3(0.0, 4665600, 0.0));
   world.particles->setAcc(pIdx[12], Vector3::Zero());
   world.particles->setMass(pIdx[12], 2.2e14);

   for(int i=0; i<NOBJ-1; i++){
      for(int j=i+1; j<NOBJ; j++){
         gravityFGs[i+j*(j-1)/2] = new Physics::fgGravity(pIdx[i], pIdx[j], 49.821763378e-11);
         world.forceGens->add(gravityFGs[i+j*(j-1)/2]);
      }
   }

   double t = 0.0;
   while(t < TMAX){
      for(int i=0; i<NOBJ; i++){
         if(world.particles->stillAlive(pIdx[i])){
            Vector3 pos = world.particles->getPos(pIdx[i]);
            std::cout<<pos[0]<<"\t"<<pos[1]<<"\t"<<pos[2]<<"\t";
         }else{
            std::cout<<"Particula "<<i<<" died"<<std::endl;
         }
      }
      std::cout<<std::endl;

      world.runPhysics(DELTAT);
      t+=DELTAT;
   }

   for(int i=0; i<NOBJ*(NOBJ-1)/2; i++){
      delete gravityFGs[i];
   }

   return 0;
}
