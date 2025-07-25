

#include "AutoGen/Optionals/OptionalArrayOfBeamoV2StringStringKeyValuePairLibrary.h"

FOptionalArrayOfBeamoV2StringStringKeyValuePair UOptionalArrayOfBeamoV2StringStringKeyValuePairLibrary::MakeOptional(TArray<UBeamoV2StringStringKeyValuePair*> Value)
{
	FOptionalArrayOfBeamoV2StringStringKeyValuePair Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfBeamoV2StringStringKeyValuePair UOptionalArrayOfBeamoV2StringStringKeyValuePairLibrary::Conv_OptionalFromValue(TArray<UBeamoV2StringStringKeyValuePair*> Value)
{
	FOptionalArrayOfBeamoV2StringStringKeyValuePair Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfBeamoV2StringStringKeyValuePairLibrary::HasValue(const FOptionalArrayOfBeamoV2StringStringKeyValuePair& Optional, TArray<UBeamoV2StringStringKeyValuePair*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UBeamoV2StringStringKeyValuePair*> UOptionalArrayOfBeamoV2StringStringKeyValuePairLibrary::GetOptionalValue(const FOptionalArrayOfBeamoV2StringStringKeyValuePair& Optional, TArray<UBeamoV2StringStringKeyValuePair*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

