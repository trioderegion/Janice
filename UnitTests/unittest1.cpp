#include "stdafx.h"
#include "CppUnitTest.h"
#include "common.h"
#include "HitPoints.h"
#include "Creature.h"
#include "World.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{		
	TEST_CLASS(AActorTests)
	{
	public:
		
		/** Basic creation method tests for objects */
		TEST_METHOD(Initialization)
		{
			/** Default actor initialization, name init to "" */
			AActor gherblin;
			Assert::AreEqual(std::string(), gherblin.GetName());

			/** Initializing an actor with a name */
			AActor not_gherblin("not_gherblin");
			const std::string next_name = "not_gherblin";
			Assert::AreEqual(next_name, not_gherblin.GetName());

		
		}

	};

	TEST_CLASS(ACreatureTests)
	{
	public:
		TEST_METHOD(Initializing)
		{
			/** Initializing a default creature (from AActor), HP init to -1 */
			ACreature gherblin_2;
			Assert::AreEqual(std::string(), gherblin_2.GetName());
			Assert::AreEqual(0, gherblin_2.HitPoints().Current());

			/** Initializing a creature with a name */
			ACreature bugbear("Bugbear");
			Assert::AreEqual(0, bugbear.HitPoints().Current());
			Assert::AreEqual(std::string("Bugbear"), bugbear.GetName());	
		}
		TEST_METHOD(Building)
		{
			ACreature training_dummy("training dummy");
			FName("Rope");
		}
	};

	TEST_CLASS(InputTests)
	{
		TEST_METHOD(SpawningActor)
		{
			FWorld world;
			auto* actor_creature = world.SpawnActor<ACreature>("training dummy");
			Assert::IsTrue(static_cast<ACreature*>(actor_creature) != nullptr);
			auto* creature = static_cast<ACreature*>(actor_creature);
			Assert::AreEqual(creature->HitPoints().Current(), 0);
			Assert::AreEqual(creature->GetName(), std::string("training dummy"));
		}
	};
}