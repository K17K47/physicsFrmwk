#ifndef PMNGR_HPP_
#define PMNGR_HPP_

#include"aux/math.hpp"
#include"particles/particle.hpp"
#include"aux/slotMap.cpp"
#include<thread>
#include<mutex>

namespace Physics{

	class pMngr{
		private:
         slotMap<Particle> reg;

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
         void remove(const unsigned idx);
         Particle& operator[](const unsigned idx);
	};
};

#endif
