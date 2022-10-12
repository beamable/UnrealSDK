

#include "OptionalArrayOfMetadataPairLibrary.h"

FOptionalArrayOfMetadataPair UOptionalArrayOfMetadataPairLibrary::MakeOptionalArrayOfMetadataPair(TArray<UMetadataPair*> Value)
{
	FOptionalArrayOfMetadataPair Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfMetadataPair UOptionalArrayOfMetadataPairLibrary::Conv_OptionalArrayOfMetadataPairFromValue(TArray<UMetadataPair*> Value)
{
	FOptionalArrayOfMetadataPair Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

