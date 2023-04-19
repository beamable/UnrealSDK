
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBeamStatsType.h"

FOptionalBeamStatsType::FOptionalBeamStatsType()
{
	Val = FBeamStatsType();
	IsSet = false;
}

FOptionalBeamStatsType::FOptionalBeamStatsType(FBeamStatsType Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalBeamStatsType::GetAddr() const { return &Val; }

void FOptionalBeamStatsType::Set(const void* Data)
{
	Val = *((FBeamStatsType*)Data);
	IsSet = true;
}