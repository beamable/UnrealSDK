
#include "BeamableCore/Public/AutoGen/Optionals/OptionalEventPhaseRuntime.h"

FOptionalEventPhaseRuntime::FOptionalEventPhaseRuntime()
{
	Val = nullptr;
	IsSet = false;
}

FOptionalEventPhaseRuntime::FOptionalEventPhaseRuntime(UEventPhaseRuntime* Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalEventPhaseRuntime::GetAddr() const { return &Val; }

void FOptionalEventPhaseRuntime::Set(const void* Data)
{
	Val = *((UEventPhaseRuntime**)Data);
	IsSet = true;
}