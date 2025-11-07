
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBeamoV2PathRuleOperationType.h"

FOptionalBeamoV2PathRuleOperationType::FOptionalBeamoV2PathRuleOperationType()
{
	Val = EBeamBeamoV2PathRuleOperationType();
	IsSet = false;
}

FOptionalBeamoV2PathRuleOperationType::FOptionalBeamoV2PathRuleOperationType(EBeamBeamoV2PathRuleOperationType Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalBeamoV2PathRuleOperationType::GetAddr() const { return &Val; }

void FOptionalBeamoV2PathRuleOperationType::Set(const void* Data)
{
	Val = *((EBeamBeamoV2PathRuleOperationType*)Data);
	IsSet = true;
}