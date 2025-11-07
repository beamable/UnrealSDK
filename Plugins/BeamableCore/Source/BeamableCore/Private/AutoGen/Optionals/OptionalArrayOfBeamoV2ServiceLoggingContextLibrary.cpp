

#include "AutoGen/Optionals/OptionalArrayOfBeamoV2ServiceLoggingContextLibrary.h"

FOptionalArrayOfBeamoV2ServiceLoggingContext UOptionalArrayOfBeamoV2ServiceLoggingContextLibrary::MakeOptional(TArray<UBeamoV2ServiceLoggingContext*> Value)
{
	FOptionalArrayOfBeamoV2ServiceLoggingContext Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfBeamoV2ServiceLoggingContext UOptionalArrayOfBeamoV2ServiceLoggingContextLibrary::Conv_OptionalFromValue(TArray<UBeamoV2ServiceLoggingContext*> Value)
{
	FOptionalArrayOfBeamoV2ServiceLoggingContext Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfBeamoV2ServiceLoggingContextLibrary::HasValue(const FOptionalArrayOfBeamoV2ServiceLoggingContext& Optional, TArray<UBeamoV2ServiceLoggingContext*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UBeamoV2ServiceLoggingContext*> UOptionalArrayOfBeamoV2ServiceLoggingContextLibrary::GetOptionalValue(const FOptionalArrayOfBeamoV2ServiceLoggingContext& Optional, TArray<UBeamoV2ServiceLoggingContext*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

