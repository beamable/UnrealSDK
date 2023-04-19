
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfCompletedStatus.h"

FOptionalArrayOfCompletedStatus::FOptionalArrayOfCompletedStatus()
{
	Val = TArray<UCompletedStatus*>();
	IsSet = false;
}

FOptionalArrayOfCompletedStatus::FOptionalArrayOfCompletedStatus(TArray<UCompletedStatus*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfCompletedStatus::GetAddr() const { return &Val; }

void FOptionalArrayOfCompletedStatus::Set(const void* Data)
{
	Val = *((TArray<UCompletedStatus*>*)Data);
	IsSet = true;
}