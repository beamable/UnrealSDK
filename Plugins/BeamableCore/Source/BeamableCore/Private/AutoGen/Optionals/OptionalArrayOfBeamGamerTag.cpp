
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfBeamGamerTag.h"

FOptionalArrayOfBeamGamerTag::FOptionalArrayOfBeamGamerTag()
{
	Val = TArray<FBeamGamerTag>();
	IsSet = false;
}

FOptionalArrayOfBeamGamerTag::FOptionalArrayOfBeamGamerTag(TArray<FBeamGamerTag> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfBeamGamerTag::GetAddr() const { return &Val; }

void FOptionalArrayOfBeamGamerTag::Set(const void* Data)
{
	Val = *((TArray<FBeamGamerTag>*)Data);
	IsSet = true;
}