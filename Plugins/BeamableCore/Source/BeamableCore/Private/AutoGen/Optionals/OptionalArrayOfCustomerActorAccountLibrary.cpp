

#include "AutoGen/Optionals/OptionalArrayOfCustomerActorAccountLibrary.h"

FOptionalArrayOfCustomerActorAccount UOptionalArrayOfCustomerActorAccountLibrary::MakeOptional(TArray<UCustomerActorAccount*> Value)
{
	FOptionalArrayOfCustomerActorAccount Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfCustomerActorAccount UOptionalArrayOfCustomerActorAccountLibrary::Conv_OptionalFromValue(TArray<UCustomerActorAccount*> Value)
{
	FOptionalArrayOfCustomerActorAccount Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfCustomerActorAccountLibrary::HasValue(const FOptionalArrayOfCustomerActorAccount& Optional, TArray<UCustomerActorAccount*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UCustomerActorAccount*> UOptionalArrayOfCustomerActorAccountLibrary::GetOptionalValue(const FOptionalArrayOfCustomerActorAccount& Optional, TArray<UCustomerActorAccount*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

