
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfEventRule.h"

FOptionalArrayOfEventRule::FOptionalArrayOfEventRule()
{
	Val = TArray<UEventRule*>();
	IsSet = false;
}

FOptionalArrayOfEventRule::FOptionalArrayOfEventRule(TArray<UEventRule*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfEventRule::GetAddr() const { return &Val; }

void FOptionalArrayOfEventRule::Set(const void* Data)
{
	Val = *((TArray<UEventRule*>*)Data);
	IsSet = true;
}