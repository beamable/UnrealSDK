

#include "OptionalArrayOfDonationRequestBodyLibrary.h"

FOptionalArrayOfDonationRequestBody UOptionalArrayOfDonationRequestBodyLibrary::MakeOptionalArrayOfDonationRequestBody(TArray<UDonationRequestBody*> Value)
{
	FOptionalArrayOfDonationRequestBody Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfDonationRequestBody UOptionalArrayOfDonationRequestBodyLibrary::Conv_OptionalArrayOfDonationRequestBodyFromValue(TArray<UDonationRequestBody*> Value)
{
	FOptionalArrayOfDonationRequestBody Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

