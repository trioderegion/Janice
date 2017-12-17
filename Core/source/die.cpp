#include "stdafx.h"
#include "common.h"
#include "die.h"
#include "time.h"
#include <numeric>

uint16 FDie::Roll() 
{
	uint16 roll = 0;

	if (NumSides() != 0)
	{
		roll = (static_cast<uint16>(rand()) % mSides) + 1;
	}

	AddToHistory(roll);
	return roll;
}

void FDie::AddToHistory(uint16 roll)
{
	mHistory.emplace_back(roll);
}





uint16 FDieSet::Roll()
{
	const uint16 result = std::accumulate(mDice.begin(), mDice.end(), 0, [](uint16 sum, FDie& die) -> uint16 { return die.Roll() + sum; });

	return result;
}