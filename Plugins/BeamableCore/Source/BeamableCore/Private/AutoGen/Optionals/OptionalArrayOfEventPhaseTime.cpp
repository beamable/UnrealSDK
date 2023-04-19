
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfEventPhaseTime.h"

FOptionalArrayOfEventPhaseTime::FOptionalArrayOfEventPhaseTime()
{
	Val = TArray<UEventPhaseTime*>();
	IsSet = false;
}

FOptionalArrayOfEventPhaseTime::FOptionalArrayOfEventPhaseTime(TArray<UEventPhaseTime*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfEventPhaseTime::GetAddr() const { return &Val; }

void FOptionalArrayOfEventPhaseTime::Set(const void* Data)
{
	Val = *((TArray<UEventPhaseTime*>*)Data);
	IsSet = true;
}