
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfServiceStatus.h"

FOptionalArrayOfServiceStatus::FOptionalArrayOfServiceStatus()
{
	Val = TArray<UServiceStatus*>();
	IsSet = false;
}

FOptionalArrayOfServiceStatus::FOptionalArrayOfServiceStatus(TArray<UServiceStatus*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfServiceStatus::GetAddr() const { return &Val; }

void FOptionalArrayOfServiceStatus::Set(const void* Data)
{
	Val = *((TArray<UServiceStatus*>*)Data);
	IsSet = true;
}