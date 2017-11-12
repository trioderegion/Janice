#include "stdafx.h"
#include "common.h"
#include "World.h"
#include "Actor.h"

FWorld::~FWorld()
{
	for (auto& actor : mActors)
	{
		delete actor.second;
	}
}

bool FWorld::CheckActorExists(const FName& name)
{
	return mActors.find(name) != mActors.end();
}
