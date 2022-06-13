/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameParticles.h
Project: CS230 final project
Author: Seulbin Seo & Junseong Park
Creation date: 6/13/2022
-----------------------------------------------------------------*/
#include "GameParticles.h"

SmokeEmitter::SmokeEmitter() : CS230::ParticleEmitter(1.0)
{
	for (int i = 0; i < SmokeEmitter::NumParticles; i++)
	{
		AddParticle(new SmokeParticle("Assets/smoke.spt"));
	}
}

HitEmitter::HitEmitter() : CS230::ParticleEmitter(1.0)
{
	for (int i = 0; i < HitEmitter::NumParticles; i++)
	{
		AddParticle(new HitParticle("Assets/hit.spt"));
	}
}

MeteorBitEmitter::MeteorBitEmitter() : CS230::ParticleEmitter(1.5)
{
	for (int i = 0; i < MeteorBitEmitter::NumParticles; i++)
	{
		AddParticle(new MeteorBit("Assets/MeteorBit.spt"));
	}
}

BloodEnitter::BloodEnitter() : CS230::ParticleEmitter(1.5)
{
	for (int i = 0; i < BloodEnitter::NumParticles; i++)
	{
		AddParticle(new BloodParticle("Assets/Blood.spt"));
	}
}
