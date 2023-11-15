
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfBeamContentId.h"

FOptionalArrayOfBeamContentId::FOptionalArrayOfBeamContentId()
{
	Val = TArray<FBeamContentId>();
	IsSet = false;
}

FOptionalArrayOfBeamContentId::FOptionalArrayOfBeamContentId(TArray<FBeamContentId> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfBeamContentId::GetAddr() const { return &Val; }

void FOptionalArrayOfBeamContentId::Set(const void* Data)
{
	Val = *((TArray<FBeamContentId>*)Data);
	IsSet = true;
}