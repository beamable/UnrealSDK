

#include "AutoGen/Optionals/OptionalBeamoV2PlayerRuleOperationTypeLibrary.h"

FOptionalBeamoV2PlayerRuleOperationType UOptionalBeamoV2PlayerRuleOperationTypeLibrary::MakeOptional(EBeamBeamoV2PlayerRuleOperationType Value)
{
	FOptionalBeamoV2PlayerRuleOperationType Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalBeamoV2PlayerRuleOperationType UOptionalBeamoV2PlayerRuleOperationTypeLibrary::Conv_OptionalFromValue(EBeamBeamoV2PlayerRuleOperationType Value)
{
	FOptionalBeamoV2PlayerRuleOperationType Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalBeamoV2PlayerRuleOperationTypeLibrary::HasValue(const FOptionalBeamoV2PlayerRuleOperationType& Optional, EBeamBeamoV2PlayerRuleOperationType& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

EBeamBeamoV2PlayerRuleOperationType UOptionalBeamoV2PlayerRuleOperationTypeLibrary::GetOptionalValue(const FOptionalBeamoV2PlayerRuleOperationType& Optional, EBeamBeamoV2PlayerRuleOperationType DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

