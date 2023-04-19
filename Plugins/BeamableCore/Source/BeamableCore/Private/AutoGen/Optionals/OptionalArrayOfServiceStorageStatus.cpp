
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfServiceStorageStatus.h"

FOptionalArrayOfServiceStorageStatus::FOptionalArrayOfServiceStorageStatus()
{
	Val = TArray<UServiceStorageStatus*>();
	IsSet = false;
}

FOptionalArrayOfServiceStorageStatus::FOptionalArrayOfServiceStorageStatus(TArray<UServiceStorageStatus*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfServiceStorageStatus::GetAddr() const { return &Val; }

void FOptionalArrayOfServiceStorageStatus::Set(const void* Data)
{
	Val = *((TArray<UServiceStorageStatus*>*)Data);
	IsSet = true;
}