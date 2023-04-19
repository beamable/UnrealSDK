
#include "BeamableCore/Public/AutoGen/Optionals/OptionalMapOfDonationRequestBody.h"

FOptionalMapOfDonationRequestBody::FOptionalMapOfDonationRequestBody()
{
	Val = TMap<FString, UDonationRequestBody*>();
	IsSet = false;
}

FOptionalMapOfDonationRequestBody::FOptionalMapOfDonationRequestBody(TMap<FString, UDonationRequestBody*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalMapOfDonationRequestBody::GetAddr() const { return &Val; }

void FOptionalMapOfDonationRequestBody::Set(const void* Data)
{
	Val = *((TMap<FString, UDonationRequestBody*>*)Data);
	IsSet = true;
}