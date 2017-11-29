#ifndef PARTICLE_HPP_
#define PARTICLE_HPP_

#include"aux/math.hpp"
#include<mutex>

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

			Vector3 getPos();
			Vector3 getVel();
			Vector3 getAcc();
			real getMass();
			real getInvMass();
			real getLife();

			void getPos(Vector3 *pos);
			void getVel(Vector3 *vel);
			void getAcc(Vector3 *acc);
			void getMass(real *m);
			void getInvMass(real *m);
			void getLife(real *l);

			bool hasFiniteMass();
			bool stillAlive();

			Vector3 getForce();
			void getForce(Vector3 *f);
			void clearForce();

         Vector3 getImpulse();
         void getImpulse(Vector3 *f);
         void clearImpulse();
	};
};

#endif
