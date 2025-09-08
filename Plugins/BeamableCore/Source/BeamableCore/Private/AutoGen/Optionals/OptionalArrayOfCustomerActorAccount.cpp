
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfCustomerActorAccount.h"

FOptionalArrayOfCustomerActorAccount::FOptionalArrayOfCustomerActorAccount()
{
	Val = TArray<UCustomerActorAccount*>();
	IsSet = false;
}

FOptionalArrayOfCustomerActorAccount::FOptionalArrayOfCustomerActorAccount(TArray<UCustomerActorAccount*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfCustomerActorAccount::GetAddr() const { return &Val; }

void FOptionalArrayOfCustomerActorAccount::Set(const void* Data)
{
	Val = *((TArray<UCustomerActorAccount*>*)Data);
	IsSet = true;
}