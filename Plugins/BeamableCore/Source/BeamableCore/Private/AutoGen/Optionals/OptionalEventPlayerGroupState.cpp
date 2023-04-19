
#include "BeamableCore/Public/AutoGen/Optionals/OptionalEventPlayerGroupState.h"

FOptionalEventPlayerGroupState::FOptionalEventPlayerGroupState()
{
	Val = nullptr;
	IsSet = false;
}

FOptionalEventPlayerGroupState::FOptionalEventPlayerGroupState(UEventPlayerGroupState* Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalEventPlayerGroupState::GetAddr() const { return &Val; }

void FOptionalEventPlayerGroupState::Set(const void* Data)
{
	Val = *((UEventPlayerGroupState**)Data);
	IsSet = true;
}