#ifndef PMNGR_HPP_
#define PMNGR_HPP_

#include"aux/math.hpp"
#include"particles/particle.hpp"
#include<thread>
#include<mutex>

namespace Physics{

	class pMngr{
		private:
         // Registry of particles proprieties
			std::vector<Vector3> pos;  //Position
			std::vector<Vector3> vel;  //Velocity
			std::vector<Vector3> acc;  //Acceleration
			std::vector<Vector3> fAcc; //Resultant Force
         std::vector<Vector3> iAcc; //Resultant Impulse

			std::vector<real> invMass; //Inverse Mass (1/m)
			std::vector<real> life; //Time left until death

         // Registry allocation tables
         std::vector<unsigned> bReference;
         std::vector<unsigned> indirection;
         std::vector<unsigned> free;

         // Registry manipulation methods
         unsigned dataInsert(Particle p); // Return inserted particle reg. index
         void dataErase(unsigned idx);

         // Integrate motion equations for particles between indexes
         // "start" and "end" over a timestep "dt"
         void integrate(real dt, unsigned start, unsigned end);

         // Things for multithreading
         unsigned ncpus = std::thread::hardware_concurrency();

         std::vector<std::thread> threads;
         std::mutex mtx;
      public:

         // Steps the particle system simulation over a timestep "dt"
         void simulateParticles(real dt);

         // Methods for particles insertion, removal and access
         unsigned newParticle();
         unsigned add(Particle p);
         unsigned add(Particle *p);
         void remove(unsigned idx);
         Particle get(unsigned idx);

         // Methods for in-place reading and editing particles
         void addForce(const unsigned idx, const Vector3 &f);
         void addImpulse(const unsigned idx, const Vector3 &i);

         void setPos(const unsigned idx, const Vector3 &position);
         void setVel(const unsigned idx, const Vector3 &vel);
         void setAcc(const unsigned idx, const Vector3 &acc);
         void setMass(const unsigned idx, const real &m);
         void setLife(const unsigned idx, const real &l);

         Vector3 getPos(const unsigned idx) const;
         Vector3 getVel(const unsigned idx) const;
         Vector3 getAcc(const unsigned idx) const;
         real getMass(const unsigned idx) const;
         real getInvMass(const unsigned idx) const;
         real getLife(const unsigned idx) const;

         void getPos(const unsigned idx, Vector3 *pos) const;
         void getVel(const unsigned idx, Vector3 *vel) const;
         void getAcc(const unsigned idx, Vector3 *acc) const;
         void getMass(const unsigned idx, real *m) const;
         void getInvMass(const unsigned idx, real *m) const;
         void getLife(const unsigned idx, real *l) const;

         bool hasFiniteMass(const unsigned idx) const;
         bool stillAlive(const unsigned idx) const;

         Vector3 getForce(const unsigned idx) const;
         void getForce(const unsigned idx, Vector3 *f) const;
         void clearForce(const unsigned idx);

         Vector3 getImpulse(const unsigned idx) const;
         void getImpulse(const unsigned idx, Vector3 *f) const;
         void clearImpulse(const unsigned idx);
	};
};

#endif
