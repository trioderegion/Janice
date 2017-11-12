#include "stdafx.h"
#include "HitPoints.h"

int32 UHitPoints::Modify(int32 modifier)
{
	mCurrent += modifier;
	return mCurrent;
}
