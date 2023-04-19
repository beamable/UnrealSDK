
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfDonationRequestBody.h"

FOptionalArrayOfDonationRequestBody::FOptionalArrayOfDonationRequestBody()
{
	Val = TArray<UDonationRequestBody*>();
	IsSet = false;
}

FOptionalArrayOfDonationRequestBody::FOptionalArrayOfDonationRequestBody(TArray<UDonationRequestBody*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfDonationRequestBody::GetAddr() const { return &Val; }

void FOptionalArrayOfDonationRequestBody::Set(const void* Data)
{
	Val = *((TArray<UDonationRequestBody*>*)Data);
	IsSet = true;
}