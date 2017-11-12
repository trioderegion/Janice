#pragma once

#include "Actor.h"

class ACreature :
	public AActor
{
public:
	ACreature() : AActor() {};
	~ACreature() = default;

	explicit ACreature(const std::string& name);

	// ACCESSORS

	/* Read current hit point value */
	UHitPoints& HitPoints() { return mHitPoints; }

private:
	UHitPoints mHitPoints;
};

