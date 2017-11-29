#ifndef PARTICLE_HPP_
#define PARTICLE_HPP_

#include"aux/math.hpp"
#include<thread>

namespace Physics{

	class Particle{
		private:
			Vector3 p = Vector3::Zero();
			Vector3 v = Vector3::Zero();
			Vector3 a = Vector3::Zero();

			Vector3 force = Vector3::Zero();
         Vector3 impulse = Vector3::Zero();

			real invMass = 0.0;

			real life = 0.0;

         std::mutex mtx;
		public:
			Particle(){};
			Particle(Vector3 pos, real mass) : p(pos),  invMass(1/mass) {}
			Particle(Vector3 pos, Vector3 vel, real mass) : p(pos), v(vel), invMass(1/mass) {}

         void integrate(real dt);

			void addForce(const Vector3 &f);
         void addImpulse(const Vector3 &i);

			void setPos(const Vector3 &pos);
			void setVel(const Vector3 &vel);
			void setAcc(const Vector3 &acc);
			void setMass(const real &m);
			void setLife(const real &l);

			Vector3 getPos() const;
			Vector3 getVel() const;
			Vector3 getAcc() const;
			real getMass() const;
			real getInvMass() const;
			real getLife() const;

			void getPos(Vector3 *pos) const;
			void getVel(Vector3 *vel) const;
			void getAcc(Vector3 *acc) const;
			void getMass(real *m) const;
			void getInvMass(real *m) const;
			void getLife(real *l) const;

			bool hasFiniteMass() const;
			bool stillAlive() const;

			Vector3 getForce() const;
			void getForce(Vector3 *f) const;
			void clearForce();

         Vector3 getImpulse() const;
         void getImpulse(Vector3 *f) const;
         void clearImpulse();
	};
};

#endif
