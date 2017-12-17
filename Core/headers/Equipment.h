#pragma once

typedef int32 FValue;
typedef int32 FWeight;


class UItem
{
public:
	UItem::UItem(const FName& name, const FValue& value, const FWeight& weight)
		: mName{ name }
		, mValue{ value }
		, mWeight{ weight }
	{
	}

	FName mName;
	FValue mValue;
	FWeight mWeight;
};
