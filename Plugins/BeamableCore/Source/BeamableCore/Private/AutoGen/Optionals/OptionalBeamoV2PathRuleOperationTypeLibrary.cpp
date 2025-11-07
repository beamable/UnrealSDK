

#include "AutoGen/Optionals/OptionalBeamoV2PathRuleOperationTypeLibrary.h"

FOptionalBeamoV2PathRuleOperationType UOptionalBeamoV2PathRuleOperationTypeLibrary::MakeOptional(EBeamBeamoV2PathRuleOperationType Value)
{
	FOptionalBeamoV2PathRuleOperationType Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalBeamoV2PathRuleOperationType UOptionalBeamoV2PathRuleOperationTypeLibrary::Conv_OptionalFromValue(EBeamBeamoV2PathRuleOperationType Value)
{
	FOptionalBeamoV2PathRuleOperationType Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalBeamoV2PathRuleOperationTypeLibrary::HasValue(const FOptionalBeamoV2PathRuleOperationType& Optional, EBeamBeamoV2PathRuleOperationType& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

EBeamBeamoV2PathRuleOperationType UOptionalBeamoV2PathRuleOperationTypeLibrary::GetOptionalValue(const FOptionalBeamoV2PathRuleOperationType& Optional, EBeamBeamoV2PathRuleOperationType DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

