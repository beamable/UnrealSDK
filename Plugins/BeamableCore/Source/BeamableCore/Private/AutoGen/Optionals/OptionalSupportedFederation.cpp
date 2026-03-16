
#include "BeamableCore/Public/AutoGen/Optionals/OptionalSupportedFederation.h"

FOptionalSupportedFederation::FOptionalSupportedFederation()
{
	Val = NewObject<USupportedFederation>(GetTransientPackage());
	IsSet = false;
}

FOptionalSupportedFederation::FOptionalSupportedFederation(USupportedFederation* Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalSupportedFederation::GetAddr() const { return &Val; }

void FOptionalSupportedFederation::Set(const void* Data)
{
	Val = *((USupportedFederation**)Data);
	IsSet = true;
}