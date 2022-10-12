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
		ensureAlwaysMsgf(GetDefault<UBeamCoreSettings>()->EditorUserSlots.Contains(x) || GetDefault<UBeamCoreSettings>()->RuntimeUserSlots.Contains(x),
		                 TEXT("Creating a non configured UserSlot is not allowed. Please register them appropriately at Project Settings > Beam Core > User Slots. USER_SLOT=%s"), *x);
	}

	Name = x;
}

FUserSlot& FUserSlot::operator=(const FString& x)
{
	// We allow setting a user slot as empty or as any Test slot. Other than those, it must be registered in the core settings.
	if (!x.IsEmpty() && !x.Contains("Test"))
	{
		ensureAlwaysMsgf(GetDefault<UBeamCoreSettings>()->EditorUserSlots.Contains(x) || GetDefault<UBeamCoreSettings>()->RuntimeUserSlots.Contains(x),
		                 TEXT("Creating a non configured UserSlot is not allowed. Please register them appropriately at Project Settings > Beam Core > User Slots. USER_SLOT=%s"), *x);
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
