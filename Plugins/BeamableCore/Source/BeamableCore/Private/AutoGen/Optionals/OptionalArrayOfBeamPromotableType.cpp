
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfBeamPromotableType.h"

FOptionalArrayOfBeamPromotableType::FOptionalArrayOfBeamPromotableType()
{
	Val = TArray<EBeamPromotableType>();
	IsSet = false;
}

FOptionalArrayOfBeamPromotableType::FOptionalArrayOfBeamPromotableType(TArray<EBeamPromotableType> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfBeamPromotableType::GetAddr() const { return &Val; }

void FOptionalArrayOfBeamPromotableType::Set(const void* Data)
{
	Val = *((TArray<EBeamPromotableType>*)Data);
	IsSet = true;
}