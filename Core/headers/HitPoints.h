#pragma once

class UHitPoints
{
public:
	UHitPoints::UHitPoints() : mCurrent{ 0 } {}
	explicit UHitPoints::UHitPoints(int32 startingHP) : mCurrent{startingHP} {}

	UHitPoints::~UHitPoints() = default;


	int32 Current() const { return mCurrent; }
	void Set(int32 newHP) { mCurrent = newHP; }
	int32 Modify(int32 modifier);


private:
	int32 mCurrent;
};
