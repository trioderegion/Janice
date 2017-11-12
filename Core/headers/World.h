#pragma once
#include <map>

class FWorld
{
public:
	FWorld::FWorld() = default;
	FWorld::~FWorld();

	template <class T>
	AActor* SpawnActor(const FName& name);

	bool CheckActorExists(const FName& name);

private:
	std::map<FName, AActor*> mActors;
};

template <class T>
AActor* FWorld::SpawnActor(const FName& name)
{
	if (CheckActorExists(name))
	{
		return nullptr;
	}
	AActor* new_actor = new T(name);
	mActors.insert(std::make_pair(name, new_actor));
	return new_actor;
}
