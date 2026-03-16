
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBeamoV2LogContextRuleAuthor.h"

FOptionalBeamoV2LogContextRuleAuthor::FOptionalBeamoV2LogContextRuleAuthor()
{
	Val = NewObject<UBeamoV2LogContextRuleAuthor>(GetTransientPackage());
	IsSet = false;
}

FOptionalBeamoV2LogContextRuleAuthor::FOptionalBeamoV2LogContextRuleAuthor(UBeamoV2LogContextRuleAuthor* Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalBeamoV2LogContextRuleAuthor::GetAddr() const { return &Val; }

void FOptionalBeamoV2LogContextRuleAuthor::Set(const void* Data)
{
	Val = *((UBeamoV2LogContextRuleAuthor**)Data);
	IsSet = true;
}