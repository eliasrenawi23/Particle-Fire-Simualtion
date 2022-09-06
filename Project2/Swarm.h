#pragma once
#include "Particle.h"

namespace ScreenP {

	class Swarm{
	public:
		const static int NPARTICLES = 5000;
	private:
		Particle*  m_pParticles;
		int lastTime;
	public:
		Swarm();
		virtual ~Swarm();
		void update(int elapsed);
		const Particle*const getParticles() { return m_pParticles; } //const pointer to Particle that is const.  (* const ) : mean that the pointer cant point to anything else
	};
}

