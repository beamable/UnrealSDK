
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfOnlineStatus.h"

FOptionalArrayOfOnlineStatus::FOptionalArrayOfOnlineStatus()
{
	Val = TArray<UOnlineStatus*>();
	IsSet = false;
}

FOptionalArrayOfOnlineStatus::FOptionalArrayOfOnlineStatus(TArray<UOnlineStatus*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfOnlineStatus::GetAddr() const { return &Val; }

void FOptionalArrayOfOnlineStatus::Set(const void* Data)
{
	Val = *((TArray<UOnlineStatus*>*)Data);
	IsSet = true;
}