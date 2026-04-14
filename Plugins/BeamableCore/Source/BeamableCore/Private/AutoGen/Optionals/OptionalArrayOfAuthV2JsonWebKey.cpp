
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfAuthV2JsonWebKey.h"

FOptionalArrayOfAuthV2JsonWebKey::FOptionalArrayOfAuthV2JsonWebKey()
{
	Val = TArray<UAuthV2JsonWebKey*>();
	IsSet = false;
}

FOptionalArrayOfAuthV2JsonWebKey::FOptionalArrayOfAuthV2JsonWebKey(TArray<UAuthV2JsonWebKey*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfAuthV2JsonWebKey::GetAddr() const { return &Val; }

void FOptionalArrayOfAuthV2JsonWebKey::Set(const void* Data)
{
	Val = *((TArray<UAuthV2JsonWebKey*>*)Data);
	IsSet = true;
}