
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBeamoV2RuleOperationType.h"

FOptionalBeamoV2RuleOperationType::FOptionalBeamoV2RuleOperationType()
{
	Val = EBeamBeamoV2RuleOperationType();
	IsSet = false;
}

FOptionalBeamoV2RuleOperationType::FOptionalBeamoV2RuleOperationType(EBeamBeamoV2RuleOperationType Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalBeamoV2RuleOperationType::GetAddr() const { return &Val; }

void FOptionalBeamoV2RuleOperationType::Set(const void* Data)
{
	Val = *((EBeamBeamoV2RuleOperationType*)Data);
	IsSet = true;
}