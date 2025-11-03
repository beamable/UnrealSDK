
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBeamoV2PlayerRuleOperationType.h"

FOptionalBeamoV2PlayerRuleOperationType::FOptionalBeamoV2PlayerRuleOperationType()
{
	Val = EBeamBeamoV2PlayerRuleOperationType();
	IsSet = false;
}

FOptionalBeamoV2PlayerRuleOperationType::FOptionalBeamoV2PlayerRuleOperationType(EBeamBeamoV2PlayerRuleOperationType Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalBeamoV2PlayerRuleOperationType::GetAddr() const { return &Val; }

void FOptionalBeamoV2PlayerRuleOperationType::Set(const void* Data)
{
	Val = *((EBeamBeamoV2PlayerRuleOperationType*)Data);
	IsSet = true;
}