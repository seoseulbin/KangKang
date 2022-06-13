/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: ParticleEmitter.cpp
Project: CS230
Author: Seulbin Seo
Creation date: 5/29/2022
-----------------------------------------------------------------*/
#include "ParticleEmitter.h"
#include "Engine.h"
#include "GameObjectManager.h"

CS230::ParticleEmitter::Particle::Particle(const std::filesystem::path& spriteFile) :GameObject({ 0, 0 }), Life(0)
{
	AddGOComponent(new CS230::Sprite(spriteFile, this));
}

void CS230::ParticleEmitter::Particle::Revive(math::vec2 newPosition, math::vec2 newVelocity, double newLife)
{
	SetPosition(newPosition);
	SetVelocity(newVelocity);
	Life = newLife;
	GetGOComponent<Sprite>()->PlayAnimation(0);
}

void CS230::ParticleEmitter::Particle::Update(double dt)
{
	if(IsAlive() == true)
	{
		Life -= dt;
		GameObject::Update(dt);
	}
}

void CS230::ParticleEmitter::Particle::Draw(math::TransformMatrix matrix)
{
	if (IsAlive() == true)
	{
		GameObject::Draw(matrix);
	}
}

CS230::ParticleEmitter::ParticleEmitter(double lifetime) : lifetime(lifetime), particleIndexToUse(0) {}

CS230::ParticleEmitter::~ParticleEmitter()
{
	particleMemoryPool.clear();
}

void CS230::ParticleEmitter::AddParticle(Particle* particleData)
{
	particleMemoryPool.push_back(particleData);

	Engine::GetGSComponent<CS230::GameObjectManager>()->Add(particleData);
}

void CS230::ParticleEmitter::Emit(int number, math::vec2 position, math::vec2 emitterVelocity, math::vec2 emitVector, double spread)
{
	for (int i = 0; i < number; i++)
	{
		if (particleMemoryPool[particleIndexToUse]->IsAlive() == true)
		{
			Engine::GetLogger().LogError("Overwrite a particle");
		}

		//particleMemoryPool[particleIndexToUse++]->Revive(position, emitterVelocity, lifetime);
		double randomAngle = rand() % static_cast<int>(spread / 2.0 - (-spread / 2.0) + 1.0) + static_cast<int>(-spread / 2.0);
		double m = ((rand() % 1024) / 2048.0f) + 0.5f;
		math::vec2 randomVelocity = math::RotateMatrix(randomAngle) * emitVector + emitterVelocity;
		randomVelocity *= m;

		particleMemoryPool[particleIndexToUse++]->Revive(position, randomVelocity, lifetime);
		if (particleIndexToUse >= particleMemoryPool.size())
		{
			particleIndexToUse = 0;
		}
	}
}
