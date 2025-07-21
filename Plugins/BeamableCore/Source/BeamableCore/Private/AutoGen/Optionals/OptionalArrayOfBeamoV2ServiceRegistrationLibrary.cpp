

#include "AutoGen/Optionals/OptionalArrayOfBeamoV2ServiceRegistrationLibrary.h"

FOptionalArrayOfBeamoV2ServiceRegistration UOptionalArrayOfBeamoV2ServiceRegistrationLibrary::MakeOptional(TArray<UBeamoV2ServiceRegistration*> Value)
{
	FOptionalArrayOfBeamoV2ServiceRegistration Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfBeamoV2ServiceRegistration UOptionalArrayOfBeamoV2ServiceRegistrationLibrary::Conv_OptionalFromValue(TArray<UBeamoV2ServiceRegistration*> Value)
{
	FOptionalArrayOfBeamoV2ServiceRegistration Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfBeamoV2ServiceRegistrationLibrary::HasValue(const FOptionalArrayOfBeamoV2ServiceRegistration& Optional, TArray<UBeamoV2ServiceRegistration*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UBeamoV2ServiceRegistration*> UOptionalArrayOfBeamoV2ServiceRegistrationLibrary::GetOptionalValue(const FOptionalArrayOfBeamoV2ServiceRegistration& Optional, TArray<UBeamoV2ServiceRegistration*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

