

#include "AutoGen/Optionals/OptionalArrayOfPlayerSessionActorPaymentTotalLibrary.h"

FOptionalArrayOfPlayerSessionActorPaymentTotal UOptionalArrayOfPlayerSessionActorPaymentTotalLibrary::MakeOptional(TArray<UPlayerSessionActorPaymentTotal*> Value)
{
	FOptionalArrayOfPlayerSessionActorPaymentTotal Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfPlayerSessionActorPaymentTotal UOptionalArrayOfPlayerSessionActorPaymentTotalLibrary::Conv_OptionalFromValue(TArray<UPlayerSessionActorPaymentTotal*> Value)
{
	FOptionalArrayOfPlayerSessionActorPaymentTotal Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfPlayerSessionActorPaymentTotalLibrary::HasValue(const FOptionalArrayOfPlayerSessionActorPaymentTotal& Optional, TArray<UPlayerSessionActorPaymentTotal*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UPlayerSessionActorPaymentTotal*> UOptionalArrayOfPlayerSessionActorPaymentTotalLibrary::GetOptionalValue(const FOptionalArrayOfPlayerSessionActorPaymentTotal& Optional, TArray<UPlayerSessionActorPaymentTotal*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

