
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfMetadataPair.h"

FOptionalArrayOfMetadataPair::FOptionalArrayOfMetadataPair()
{
	Val = TArray<UMetadataPair*>();
	IsSet = false;
}

FOptionalArrayOfMetadataPair::FOptionalArrayOfMetadataPair(TArray<UMetadataPair*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfMetadataPair::GetAddr() const { return &Val; }

void FOptionalArrayOfMetadataPair::Set(const void* Data)
{
	Val = *((TArray<UMetadataPair*>*)Data);
	IsSet = true;
}