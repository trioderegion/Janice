#include "stdafx.h"
#include "CppUnitTest.h"
#include "common.h"
#include "HitPoints.h"
#include "Creature.h"
#include "World.h"
#include "die.h"
#include <ctime>
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{		
	TEST_CLASS(ActorTests)
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

	TEST_CLASS(CreatureTests)
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
		}
	};

	TEST_CLASS(WorldTests)
	{
		TEST_METHOD(SpawningActor)
		{
			FWorld world;

			/* add actor and cast to parent type. Then cast back down and access ACreature only members. */
			AActor* actor_creature = world.SpawnActor<ACreature>("training dummy");
			Assert::IsTrue(dynamic_cast<ACreature*>(actor_creature) != nullptr);
			ACreature* creature = dynamic_cast<ACreature*>(actor_creature);
			Assert::AreEqual(creature->HitPoints().Current(), 0);
			Assert::AreEqual(creature->GetName(), std::string("training dummy"));

			/* Spawn an actor and try to cast down to a creature */
			auto* plain_actor = world.SpawnActor<AActor>("actor");
			Assert::IsTrue(dynamic_cast<ACreature*>(plain_actor) == nullptr);
		}
	};

	TEST_CLASS(Equipment)
	{
		TEST_METHOD(CreatingItem)
		{
			
		}
	};

	TEST_CLASS(Dice)
	{
		/** Testing for correct range on die rolls */
		TEST_METHOD(RangeChecking)
		{
			srand(static_cast<unsigned int>(time(NULL)));

			for(int size : {1,6,20})
			{
				FDie die(size);
				for (int iteration = 0; iteration < 1000; iteration++)
				{
					uint16 result = die.Roll();
					std::cout << result;
					Assert::IsTrue(result >= 1);
					Assert::IsTrue(result <= size);
				}

				const auto& history = die.GetHistory();
				std::vector<int32> results(die.NumSides());
				results.empty();
				for (const auto& element : history)
				{
					results[element-1]++;
				}

				if (die.NumSides() == 1)
				{
					//ensure only element 0 is populated and that all other entries are 0
					int32 numRolls = results[0];
					Assert::IsTrue(numRolls == 1000);
					Assert::IsTrue(results.size() == 1);

				}
				else
				{
					//ensure each number appears at least once
					for (const auto& count : results)
					{
						Assert::IsTrue(count > 0);
						Assert::IsTrue(count < 1000);
					}
				}

			}

			//check that silly d0's work
			FDie d0(0);
			uint16 result = d0.Roll();
			Assert::IsTrue(result == 0);
		}

		TEST_METHOD(SetCreation)
		{
			FDieSet threeD6(3, 6);

			for (int iteration = 0; iteration < 1000; iteration++)
			{
				auto result = threeD6.Roll();
				Assert::IsTrue(result >= 3);
				Assert::IsTrue(result <= 18);
			}
		}
	};

}