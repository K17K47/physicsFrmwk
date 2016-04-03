#ifndef PWORLD_HPP_
#define PWORLD_HPP_

#include"aux/math.hpp"
#include"particles/particle.hpp"

namespace Physics{
	class pWorld{
		private:
			std::vector<Vector3> pos;
			std::vector<Vector3> vel;
			std::vector<Vector3> acc;
			std::vector<Vector3> fAcc;

			std::vector<real> invMass;
			std::vector<real> life;

         std::vector<unsigned> bReference;
         std::vector<unsigned> indirection;
         std::vector<unsigned> free;

         unsigned dataInsert(Particle p);
         void dataErase(unsigned idx);

         void integrate(real dt);
      public:

         void simulateParticles(real dt);

         unsigned addParticle(Particle p);
         unsigned addParticle(Particle *p);
         void rmParticle(unsigned idx);

         Particle getParticle(unsigned idx);

         void addForce(const unsigned idx, const Vector3 &f);

         void setPos(const unsigned idx, const Vector3 &pos);
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
	};
};

#endif
