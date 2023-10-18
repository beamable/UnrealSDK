#include "UserSlots/UserSlot.h"

#include "BeamCoreSettings.h"

FUserSlot::FUserSlot()
{
}

FUserSlot::FUserSlot(const FString& x)
{
	// We allow setting a user slot as empty or as any Test slot. Other than those, it must be registered in the core settings. 
	if (!x.IsEmpty() && !x.Contains("Test"))
	{
		if (x.StartsWith("PIE_"))
		{
			int32 Idx;
			if (const auto SubtractPie = x.Right(4); SubtractPie.FindChar('_', Idx))
			{
				const auto SubtractPieInstance = SubtractPie.Right(Idx + 1);
				ensureAlwaysMsgf(GetDefault<UBeamCoreSettings>()->RuntimeUserSlots.Contains(SubtractPieInstance) || GetDefault<UBeamCoreSettings>()->DeveloperUserSlots.Contains(SubtractPieInstance),
								 TEXT("Creating a non configured UserSlot is not allowed. Please register them appropriately at Project Settings > Beam Core > User Slots. USER_SLOT=%s"), *x);
			}
		}
		else
		{
			ensureAlwaysMsgf(GetDefault<UBeamCoreSettings>()->RuntimeUserSlots.Contains(x) || GetDefault<UBeamCoreSettings>()->DeveloperUserSlots.Contains(x),
							 TEXT("Creating a non configured UserSlot is not allowed. Please register them appropriately at Project Settings > Beam Core > User Slots. USER_SLOT=%s"), *x);
		}
	}

	Name = x;
}

FUserSlot& FUserSlot::operator=(const FString& x)
{
	// We allow setting a user slot as empty or as any Test slot. Other than those, it must be registered in the core settings.
	if (!x.IsEmpty() && !x.Contains("Test"))
	{
		if (x.StartsWith("PIE_"))
		{
			int32 Idx;
			if (const auto SubtractPie = x.Right(4); SubtractPie.FindChar('_', Idx))
			{
				const auto SubtractPieInstance = SubtractPie.Right(Idx + 1);
				ensureAlwaysMsgf(GetDefault<UBeamCoreSettings>()->RuntimeUserSlots.Contains(SubtractPieInstance) || GetDefault<UBeamCoreSettings>()->DeveloperUserSlots.Contains(SubtractPieInstance),
				                 TEXT("Creating a non configured UserSlot is not allowed. Please register them appropriately at Project Settings > Beam Core > User Slots. USER_SLOT=%s"), *x);
			}
		}
		else
		{
			ensureAlwaysMsgf(GetDefault<UBeamCoreSettings>()->RuntimeUserSlots.Contains(x) || GetDefault<UBeamCoreSettings>()->DeveloperUserSlots.Contains(x),
			                 TEXT("Creating a non configured UserSlot is not allowed. Please register them appropriately at Project Settings > Beam Core > User Slots. USER_SLOT=%s"), *x);
		}
	}

	this->Name = x;
	return *this;
}

bool FUserSlot::operator==(const FUserSlot& Other) const
{
	return Equals(Other);
}

bool FUserSlot::Equals(const FUserSlot& Other) const
{
	return Name.Equals(Other.Name);
}

FUserSlot::operator FString()
{
	return Name;
}
