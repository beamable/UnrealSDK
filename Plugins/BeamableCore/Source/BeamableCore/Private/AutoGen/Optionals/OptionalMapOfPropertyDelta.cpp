
#include "BeamableCore/Public/AutoGen/Optionals/OptionalMapOfPropertyDelta.h"

FOptionalMapOfPropertyDelta::FOptionalMapOfPropertyDelta()
{
	Val = TMap<FString, UPropertyDelta*>();
	IsSet = false;
}

FOptionalMapOfPropertyDelta::FOptionalMapOfPropertyDelta(TMap<FString, UPropertyDelta*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalMapOfPropertyDelta::GetAddr() const { return &Val; }

void FOptionalMapOfPropertyDelta::Set(const void* Data)
{
	Val = *((TMap<FString, UPropertyDelta*>*)Data);
	IsSet = true;
}