

#include "AutoGen/Optionals/OptionalArrayOfMetadataPairLibrary.h"

FOptionalArrayOfMetadataPair UOptionalArrayOfMetadataPairLibrary::MakeOptional(TArray<UMetadataPair*> Value)
{
	FOptionalArrayOfMetadataPair Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfMetadataPair UOptionalArrayOfMetadataPairLibrary::Conv_OptionalFromValue(TArray<UMetadataPair*> Value)
{
	FOptionalArrayOfMetadataPair Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfMetadataPairLibrary::HasValue(const FOptionalArrayOfMetadataPair& Optional, TArray<UMetadataPair*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UMetadataPair*> UOptionalArrayOfMetadataPairLibrary::GetOptionalValue(const FOptionalArrayOfMetadataPair& Optional, TArray<UMetadataPair*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

