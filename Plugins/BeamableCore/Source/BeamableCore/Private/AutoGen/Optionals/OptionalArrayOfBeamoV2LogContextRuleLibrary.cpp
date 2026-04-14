

#include "AutoGen/Optionals/OptionalArrayOfBeamoV2LogContextRuleLibrary.h"

FOptionalArrayOfBeamoV2LogContextRule UOptionalArrayOfBeamoV2LogContextRuleLibrary::MakeOptional(TArray<UBeamoV2LogContextRule*> Value)
{
	FOptionalArrayOfBeamoV2LogContextRule Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfBeamoV2LogContextRule UOptionalArrayOfBeamoV2LogContextRuleLibrary::Conv_OptionalFromValue(TArray<UBeamoV2LogContextRule*> Value)
{
	FOptionalArrayOfBeamoV2LogContextRule Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfBeamoV2LogContextRuleLibrary::HasValue(const FOptionalArrayOfBeamoV2LogContextRule& Optional, TArray<UBeamoV2LogContextRule*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UBeamoV2LogContextRule*> UOptionalArrayOfBeamoV2LogContextRuleLibrary::GetOptionalValue(const FOptionalArrayOfBeamoV2LogContextRule& Optional, TArray<UBeamoV2LogContextRule*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

