

#include "AutoGen/Optionals/OptionalArrayOfCustomerActorCustomerLibrary.h"

FOptionalArrayOfCustomerActorCustomer UOptionalArrayOfCustomerActorCustomerLibrary::MakeOptional(TArray<UCustomerActorCustomer*> Value)
{
	FOptionalArrayOfCustomerActorCustomer Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfCustomerActorCustomer UOptionalArrayOfCustomerActorCustomerLibrary::Conv_OptionalFromValue(TArray<UCustomerActorCustomer*> Value)
{
	FOptionalArrayOfCustomerActorCustomer Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfCustomerActorCustomerLibrary::HasValue(const FOptionalArrayOfCustomerActorCustomer& Optional, TArray<UCustomerActorCustomer*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UCustomerActorCustomer*> UOptionalArrayOfCustomerActorCustomerLibrary::GetOptionalValue(const FOptionalArrayOfCustomerActorCustomer& Optional, TArray<UCustomerActorCustomer*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

