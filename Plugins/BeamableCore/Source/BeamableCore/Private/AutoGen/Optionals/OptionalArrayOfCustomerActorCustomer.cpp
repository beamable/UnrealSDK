
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfCustomerActorCustomer.h"

FOptionalArrayOfCustomerActorCustomer::FOptionalArrayOfCustomerActorCustomer()
{
	Val = TArray<UCustomerActorCustomer*>();
	IsSet = false;
}

FOptionalArrayOfCustomerActorCustomer::FOptionalArrayOfCustomerActorCustomer(TArray<UCustomerActorCustomer*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfCustomerActorCustomer::GetAddr() const { return &Val; }

void FOptionalArrayOfCustomerActorCustomer::Set(const void* Data)
{
	Val = *((TArray<UCustomerActorCustomer*>*)Data);
	IsSet = true;
}