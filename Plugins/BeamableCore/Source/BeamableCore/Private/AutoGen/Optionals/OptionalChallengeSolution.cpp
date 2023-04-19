
#include "BeamableCore/Public/AutoGen/Optionals/OptionalChallengeSolution.h"

FOptionalChallengeSolution::FOptionalChallengeSolution()
{
	Val = nullptr;
	IsSet = false;
}

FOptionalChallengeSolution::FOptionalChallengeSolution(UChallengeSolution* Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalChallengeSolution::GetAddr() const { return &Val; }

void FOptionalChallengeSolution::Set(const void* Data)
{
	Val = *((UChallengeSolution**)Data);
	IsSet = true;
}