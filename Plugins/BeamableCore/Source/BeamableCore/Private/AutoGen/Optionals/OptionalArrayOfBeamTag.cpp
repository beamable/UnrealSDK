
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfBeamTag.h"

FOptionalArrayOfBeamTag::FOptionalArrayOfBeamTag()
{
	Val = TArray<FBeamTag>();
	IsSet = false;
}

FOptionalArrayOfBeamTag::FOptionalArrayOfBeamTag(TArray<FBeamTag> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfBeamTag::GetAddr() const { return &Val; }

void FOptionalArrayOfBeamTag::Set(const void* Data)
{
	Val = *((TArray<FBeamTag>*)Data);
	IsSet = true;
}