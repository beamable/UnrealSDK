

#include "AutoGen/Optionals/OptionalArrayOfBeamoV2FederationRegistrationLibrary.h"

FOptionalArrayOfBeamoV2FederationRegistration UOptionalArrayOfBeamoV2FederationRegistrationLibrary::MakeOptional(TArray<UBeamoV2FederationRegistration*> Value)
{
	FOptionalArrayOfBeamoV2FederationRegistration Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfBeamoV2FederationRegistration UOptionalArrayOfBeamoV2FederationRegistrationLibrary::Conv_OptionalFromValue(TArray<UBeamoV2FederationRegistration*> Value)
{
	FOptionalArrayOfBeamoV2FederationRegistration Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfBeamoV2FederationRegistrationLibrary::HasValue(const FOptionalArrayOfBeamoV2FederationRegistration& Optional, TArray<UBeamoV2FederationRegistration*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UBeamoV2FederationRegistration*> UOptionalArrayOfBeamoV2FederationRegistrationLibrary::GetOptionalValue(const FOptionalArrayOfBeamoV2FederationRegistration& Optional, TArray<UBeamoV2FederationRegistration*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

