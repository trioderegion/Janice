#pragma once
#include "die.h"
#include "Equipment.h"

enum class EWeaponCategory : int8
{
	None = -1,
	Simple = 0,
	Martial = 1,
	Ranged = 2,
	Melee = 3
};

enum class EWeaponTag : int8
{
	Ammunition,
	Thrown,
	Heavy,
	TwoHanded,
	Versatile,
	Finesse,
	Light
};

/**
 * \brief Assigns weapon properties to a piece of equipment
 */
class UWeapon : UItem
{
public:
	UWeapon::UWeapon(const UItem& item, const std::vector<EWeaponCategory>& categories, const std::vector<EWeaponTag>& weaponTags, const FDieSet& damageDie)
		: UItem{item}
		, mDamageDie{ damageDie }
		, mCategories{ categories }
		, mTags{ weaponTags }
	{
	}

	const FDieSet& GetDamageDie() const { return mDamageDie; }

	bool Attach(ACreature* creature)
	{
		if (creature == nullptr)
		{
			return false;
		}

		mOwner = creature;
		return true;
	}

	uint16 RollDamage()
	{
		return mDamageDie.Roll();
	}

private:
	FDieSet mDamageDie;
	std::vector<EWeaponCategory> mCategories;
	std::vector<EWeaponTag> mTags;
	ACreature* mOwner{nullptr};
};