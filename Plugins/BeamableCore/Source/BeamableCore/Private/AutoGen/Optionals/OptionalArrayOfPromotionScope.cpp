
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfPromotionScope.h"

FOptionalArrayOfPromotionScope::FOptionalArrayOfPromotionScope()
{
	Val = TArray<UPromotionScope*>();
	IsSet = false;
}

FOptionalArrayOfPromotionScope::FOptionalArrayOfPromotionScope(TArray<UPromotionScope*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfPromotionScope::GetAddr() const { return &Val; }

void FOptionalArrayOfPromotionScope::Set(const void* Data)
{
	Val = *((TArray<UPromotionScope*>*)Data);
	IsSet = true;
}