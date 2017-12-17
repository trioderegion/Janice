#pragma once
#include <list>

class FDie
{
public:
	FDie::FDie(uint16 sides)
		: mSides{sides}
	{
	}

	uint16 Roll();

	auto NumSides() const
	{
		return mSides;
	}

	const auto& GetHistory() const
	{
		return mHistory;
	}

private:
	void AddToHistory(uint16 roll);

	uint16 mSides{ 1 };
	std::list<uint16> mHistory;
};

class FDieSet
{
public:
	FDieSet::FDieSet(std::vector<FDie>& dice)
		: mDice{dice}
	{
		
	}

	FDieSet::FDieSet(int16 num, uint16 size)
	{
		mDice = std::vector<FDie>(num, FDie(size));
	}

	uint16 Roll();


private:
	std::vector<FDie> mDice;
};