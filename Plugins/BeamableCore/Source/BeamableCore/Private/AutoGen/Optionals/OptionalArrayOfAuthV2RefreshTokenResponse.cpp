
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfAuthV2RefreshTokenResponse.h"

FOptionalArrayOfAuthV2RefreshTokenResponse::FOptionalArrayOfAuthV2RefreshTokenResponse()
{
	Val = TArray<UAuthV2RefreshTokenResponse*>();
	IsSet = false;
}

FOptionalArrayOfAuthV2RefreshTokenResponse::FOptionalArrayOfAuthV2RefreshTokenResponse(TArray<UAuthV2RefreshTokenResponse*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfAuthV2RefreshTokenResponse::GetAddr() const { return &Val; }

void FOptionalArrayOfAuthV2RefreshTokenResponse::Set(const void* Data)
{
	Val = *((TArray<UAuthV2RefreshTokenResponse*>*)Data);
	IsSet = true;
}