/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameParticles.h
Project: CS230
Author: Seulbin Seo
Creation date: 5/29/2022
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

