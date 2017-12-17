#pragma once

typedef double FValue;
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

	const auto& GetName() const
	{
		return mName;
	}
	 
	const auto& GetValue() const
	{
		return mValue;
	}

	const auto& GetWeight() const
	{
		return mWeight;
	}

private:
	FName mName;
	FValue mValue;
	FWeight mWeight;
};
