

#include "AutoGen/Optionals/OptionalMapOfDonationRequestBodyLibrary.h"

FOptionalMapOfDonationRequestBody UOptionalMapOfDonationRequestBodyLibrary::MakeOptional(TMap<FString, UDonationRequestBody*> Value)
{
	FOptionalMapOfDonationRequestBody Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalMapOfDonationRequestBody UOptionalMapOfDonationRequestBodyLibrary::Conv_OptionalFromValue(TMap<FString, UDonationRequestBody*> Value)
{
	FOptionalMapOfDonationRequestBody Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalMapOfDonationRequestBodyLibrary::HasValue(const FOptionalMapOfDonationRequestBody& Optional, TMap<FString, UDonationRequestBody*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TMap<FString, UDonationRequestBody*> UOptionalMapOfDonationRequestBodyLibrary::GetOptionalValue(const FOptionalMapOfDonationRequestBody& Optional, TMap<FString, UDonationRequestBody*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

