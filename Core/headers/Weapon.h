#pragma once
#include "die.h"
#include "Equipment.h"

enum class EWeaponCategory : int8
{
	None,
	Simple,
	Martial,
	Ranged,
	Melee
};

/**
 * \brief Assigns weapon properties to a piece of equipment
 */
class UWeapon : UItem
{
public:
	UWeapon::UWeapon(const UItem& item, std::vector<EWeaponCategory>& categories, const FDieSet& damageDie)
		: UItem{item}
		, mDamageDie{ damageDie }
		, mCategories{ categories }
	{
	}

private:
	FDieSet mDamageDie;
	std::vector<EWeaponCategory> mCategories;
};