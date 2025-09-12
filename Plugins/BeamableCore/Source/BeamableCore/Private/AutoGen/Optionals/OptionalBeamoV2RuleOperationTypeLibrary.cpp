

#include "AutoGen/Optionals/OptionalBeamoV2RuleOperationTypeLibrary.h"

FOptionalBeamoV2RuleOperationType UOptionalBeamoV2RuleOperationTypeLibrary::MakeOptional(EBeamBeamoV2RuleOperationType Value)
{
	FOptionalBeamoV2RuleOperationType Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalBeamoV2RuleOperationType UOptionalBeamoV2RuleOperationTypeLibrary::Conv_OptionalFromValue(EBeamBeamoV2RuleOperationType Value)
{
	FOptionalBeamoV2RuleOperationType Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalBeamoV2RuleOperationTypeLibrary::HasValue(const FOptionalBeamoV2RuleOperationType& Optional, EBeamBeamoV2RuleOperationType& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

EBeamBeamoV2RuleOperationType UOptionalBeamoV2RuleOperationTypeLibrary::GetOptionalValue(const FOptionalBeamoV2RuleOperationType& Optional, EBeamBeamoV2RuleOperationType DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

