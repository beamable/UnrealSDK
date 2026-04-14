
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfRealmAssociation.h"

FOptionalArrayOfRealmAssociation::FOptionalArrayOfRealmAssociation()
{
	Val = TArray<URealmAssociation*>();
	IsSet = false;
}

FOptionalArrayOfRealmAssociation::FOptionalArrayOfRealmAssociation(TArray<URealmAssociation*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfRealmAssociation::GetAddr() const { return &Val; }

void FOptionalArrayOfRealmAssociation::Set(const void* Data)
{
	Val = *((TArray<URealmAssociation*>*)Data);
	IsSet = true;
}