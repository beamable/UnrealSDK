
#include "BeamableCore/Public/AutoGen/Optionals/OptionalMapOfDouble.h"

FOptionalMapOfDouble::FOptionalMapOfDouble()
{
	Val = TMap<FString, double>();
	IsSet = false;
}

FOptionalMapOfDouble::FOptionalMapOfDouble(TMap<FString, double> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalMapOfDouble::GetAddr() const { return &Val; }

void FOptionalMapOfDouble::Set(const void* Data)
{
	Val = *((TMap<FString, double>*)Data);
	IsSet = true;
}