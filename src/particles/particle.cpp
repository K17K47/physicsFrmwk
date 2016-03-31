#include "particle.h"

namespace Physics{

	void Particle::addForce(const Vector3 &f){
		force += f;
	}

        void Particle::setPos(const Vector3 &pos){
		p = pos;
	}

        void Particle::setVel(const Vector3 &vel){
		v = vel;
	}

        void Particle::setAcc(const Vector3 &acc){
		a = acc;
	}

        void Particle::setMass(const real &m){
		invMass = 1.0/m;
	}

	void Particle::setLife(const real &l){
		life = l;
	}

        Vector3 Particle::getPos() const{
		return p;
	}

        Vector3 Particle::getVel() const{
		return v;
	}

        Vector3 Particle::getAcc() const{
		return a;
	}

        real Particle::getMass() const{
		if(!hasFiniteMass()){
			return REAL_MAX;
		}else{
			return 1.0/invMass;
		}
	}

        real Particle::getInvMass() const{
		return invMass;
	}

	real Particle::getLife() const{
		return life;
	}

        void Particle::getPos(Vector3 *pos) const{
		*pos = p;
	}

        void Particle::getVel(Vector3 *vel) const{
		*vel = v;
	}

        void Particle::getAcc(Vector3 *acc) const{
		*acc = a;
	}

        void Particle::getMass(real *m) const{
		if(!hasFiniteMass()){
			*m = REAL_MAX;
		}else{
			*m = 1.0/invMass;
		}
	}

        void Particle::getInvMass(real *m) const{
		*m = invMass;
	}

	void Particle::getLife(real *l) const{
		*l = life;
	}

        bool Particle::hasFiniteMass() const{
		if(invMass <= 0.0){
			return false;
		}else{
			return true;
		}
	}

	bool Particle::stillAlive() const{
		if(life <= 0.0){
			return false;
		}else{
			return true;
		}
	}

        Vector3 Particle::getForce() const{
		return force;
	}

        void Particle::getForce(Vector3 *f) const{
		*f = force;
	}

        void Particle::clearForce(){
		force = Vector3::Zero();
	}

};
