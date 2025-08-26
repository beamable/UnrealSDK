
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfPromotion.h"

FOptionalArrayOfPromotion::FOptionalArrayOfPromotion()
{
	Val = TArray<UPromotion*>();
	IsSet = false;
}

FOptionalArrayOfPromotion::FOptionalArrayOfPromotion(TArray<UPromotion*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfPromotion::GetAddr() const { return &Val; }

void FOptionalArrayOfPromotion::Set(const void* Data)
{
	Val = *((TArray<UPromotion*>*)Data);
	IsSet = true;
}