#include "stdafx.h"
#include "CppUnitTest.h"
#include "common.h"
#include "HitPoints.h"
#include "Creature.h"
#include "World.h"
#include "die.h"
#include <ctime>
#include <iostream>
#include "Equipment.h"
#include "Weapon.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;



namespace UnitTests
{		
	//Not a perfect range check but it will catch serious errors
	//create genFunc by passing an in-place lamba that returns a single iteration of a number generation
	auto range_check = [](int numIterations, auto genFunc, auto minResult, auto maxResult)
	{
		bool pass = true;
		for (int iteration = 0; iteration < numIterations; iteration++)
		{
			const auto result = genFunc();
			pass &= (result >= minResult);
			pass &= (result <= maxResult);
		}

		return pass;
	};

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
			std::string abacus_name("Abacus");
			std::string acid_name("Acid (vial)");
			UItem abacus(abacus_name, 2, 2);
			UItem acid(acid_name, 25, 1);

			Assert::IsTrue(abacus.GetName() == abacus_name);
			Assert::IsTrue(acid.GetName() == acid_name);
			
			Assert::IsTrue(abacus.GetValue() == 2);
			Assert::IsTrue(acid.GetValue() == 25);

			Assert::IsTrue(abacus.GetWeight() == 2);
			Assert::IsTrue(acid.GetWeight() == 1);
		}

		TEST_METHOD(CreatingWeapon)
		{
			UWeapon mace(UItem("Mace", .1, 2), { EWeaponCategory::Simple, EWeaponCategory::Melee }, {}, FDieSet(1, 6));

			FDieSet mace_damage_die = mace.GetDamageDie();

			//check that the damage die is correct
			auto roll_func = [&mace_damage_die]() {return mace_damage_die.Roll(); };
			range_check(1000, roll_func, 1, 6);

		}

		TEST_METHOD(RawWeaponDamage)
		{
			UWeapon mace(UItem("Mace", .1, 2), { EWeaponCategory::Simple, EWeaponCategory::Melee }, {}, FDieSet(1, 6));

			auto damage_roll = [&mace]() { return mace.RollDamage(); };
			range_check(1000, damage_roll, 1, 6);
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

				auto roll_func = [&die]() { return die.Roll(); };
				Assert::IsTrue(range_check(1000, roll_func, 1, size));
				const auto& history = die.GetHistory();
				std::vector<int32> results(die.NumSides());
				results.empty();
				for (const auto& roll : history)
				{
					//store in element = roll-1 (for indexing reasons, ya dofus)
					results[roll-1]++;
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
			auto roll_func = [&d0]() {return d0.Roll(); };
			range_check(1000, roll_func, 0, 0);
		}

		TEST_METHOD(SetCreation)
		{
			FDieSet threeD6(3, 6);

			//ensuring a 3d6 roll falls inside the expected range
			auto roll_func = [&threeD6]() { return threeD6.Roll(); };
			Assert::IsFalse(range_check(1000, roll_func, 3, 5));
			Assert::IsTrue(range_check(1000, roll_func, 3, 18));
		}

	};

}