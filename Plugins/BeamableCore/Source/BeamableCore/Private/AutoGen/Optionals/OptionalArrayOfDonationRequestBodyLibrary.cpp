

#include "AutoGen/Optionals/OptionalArrayOfDonationRequestBodyLibrary.h"

FOptionalArrayOfDonationRequestBody UOptionalArrayOfDonationRequestBodyLibrary::MakeOptional(TArray<UDonationRequestBody*> Value)
{
	FOptionalArrayOfDonationRequestBody Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfDonationRequestBody UOptionalArrayOfDonationRequestBodyLibrary::Conv_OptionalFromValue(TArray<UDonationRequestBody*> Value)
{
	FOptionalArrayOfDonationRequestBody Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfDonationRequestBodyLibrary::HasValue(const FOptionalArrayOfDonationRequestBody& Optional, TArray<UDonationRequestBody*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UDonationRequestBody*> UOptionalArrayOfDonationRequestBodyLibrary::GetOptionalValue(const FOptionalArrayOfDonationRequestBody& Optional, TArray<UDonationRequestBody*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

