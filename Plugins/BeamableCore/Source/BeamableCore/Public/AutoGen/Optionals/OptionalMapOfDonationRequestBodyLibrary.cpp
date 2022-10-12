

#include "OptionalMapOfDonationRequestBodyLibrary.h"

FOptionalMapOfDonationRequestBody UOptionalMapOfDonationRequestBodyLibrary::MakeOptionalMapOfDonationRequestBody(TMap<FString, UDonationRequestBody*> Value)
{
	FOptionalMapOfDonationRequestBody Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalMapOfDonationRequestBody UOptionalMapOfDonationRequestBodyLibrary::Conv_OptionalMapOfDonationRequestBodyFromValue(TMap<FString, UDonationRequestBody*> Value)
{
	FOptionalMapOfDonationRequestBody Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

