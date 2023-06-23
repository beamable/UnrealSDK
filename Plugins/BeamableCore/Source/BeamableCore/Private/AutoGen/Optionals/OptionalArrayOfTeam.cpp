
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfTeam.h"

FOptionalArrayOfTeam::FOptionalArrayOfTeam()
{
	Val = TArray<UTeam*>();
	IsSet = false;
}

FOptionalArrayOfTeam::FOptionalArrayOfTeam(TArray<UTeam*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfTeam::GetAddr() const { return &Val; }

void FOptionalArrayOfTeam::Set(const void* Data)
{
	Val = *((TArray<UTeam*>*)Data);
	IsSet = true;
}