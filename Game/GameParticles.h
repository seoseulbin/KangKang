/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameParticles.h
Project: CS230 final project
Author: Seulbin Seo & Junseong Park
Creation date: 6/13/2022
-----------------------------------------------------------------*/
#pragma once
#include "../Engine/ParticleEmitter.h"
#include "GameObjectTypes.h"

class SmokeEmitter : public CS230::ParticleEmitter {
public:
    SmokeEmitter();
private:
    class SmokeParticle : public CS230::ParticleEmitter::Particle {
    public:
        SmokeParticle(std::string spriteFile) : CS230::ParticleEmitter::Particle(spriteFile) {}
        GameObjectType GetObjectType() { return GameObjectType::Particle; }
        std::string GetObjectTypeName() { return "Smoke Particle"; }
    };
    static constexpr int NumParticles = 20;
};

class HitEmitter : public CS230::ParticleEmitter {
public:
    HitEmitter();
private:
    class HitParticle : public CS230::ParticleEmitter::Particle {
    public:
        HitParticle(std::string spriteFile) : CS230::ParticleEmitter::Particle(spriteFile) {}
        GameObjectType GetObjectType() { return GameObjectType::Particle; }
        std::string GetObjectTypeName() { return "Hit Particle"; }
    };
    static constexpr int NumParticles = 10;
};

class MeteorBitEmitter : public CS230::ParticleEmitter {
public:
    MeteorBitEmitter();
private:
    class MeteorBit : public CS230::ParticleEmitter::Particle {
    public:
        MeteorBit(std::string spriteFile) : CS230::ParticleEmitter::Particle(spriteFile) {}
        GameObjectType GetObjectType() { return GameObjectType::Particle; }
        std::string GetObjectTypeName() { return "Meteor Bit Particle"; }
    };
    static constexpr int NumParticles = 150;
};

class BloodEnitter : public CS230::ParticleEmitter {
public:
    BloodEnitter();
private:
    class BloodParticle : public CS230::ParticleEmitter::Particle {
    public:
        BloodParticle(std::string spriteFile) : CS230::ParticleEmitter::Particle(spriteFile) {}
        GameObjectType GetObjectType() { return GameObjectType::Particle; }
        std::string GetObjectTypeName() { return "Blood Particle"; }
    };
    static constexpr int NumParticles = 150;
};