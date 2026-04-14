
#include "BeamableCore/Public/AutoGen/Optionals/OptionalAuthV2ChallengeSolution.h"

FOptionalAuthV2ChallengeSolution::FOptionalAuthV2ChallengeSolution()
{
	Val = NewObject<UAuthV2ChallengeSolution>(GetTransientPackage());
	IsSet = false;
}

FOptionalAuthV2ChallengeSolution::FOptionalAuthV2ChallengeSolution(UAuthV2ChallengeSolution* Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalAuthV2ChallengeSolution::GetAddr() const { return &Val; }

void FOptionalAuthV2ChallengeSolution::Set(const void* Data)
{
	Val = *((UAuthV2ChallengeSolution**)Data);
	IsSet = true;
}