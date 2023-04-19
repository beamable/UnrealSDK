
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfPlayerStatRequirement.h"

FOptionalArrayOfPlayerStatRequirement::FOptionalArrayOfPlayerStatRequirement()
{
	Val = TArray<UPlayerStatRequirement*>();
	IsSet = false;
}

FOptionalArrayOfPlayerStatRequirement::FOptionalArrayOfPlayerStatRequirement(TArray<UPlayerStatRequirement*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfPlayerStatRequirement::GetAddr() const { return &Val; }

void FOptionalArrayOfPlayerStatRequirement::Set(const void* Data)
{
	Val = *((TArray<UPlayerStatRequirement*>*)Data);
	IsSet = true;
}