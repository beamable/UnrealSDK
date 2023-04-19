
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfScheduleDefinition.h"

FOptionalArrayOfScheduleDefinition::FOptionalArrayOfScheduleDefinition()
{
	Val = TArray<UScheduleDefinition*>();
	IsSet = false;
}

FOptionalArrayOfScheduleDefinition::FOptionalArrayOfScheduleDefinition(TArray<UScheduleDefinition*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfScheduleDefinition::GetAddr() const { return &Val; }

void FOptionalArrayOfScheduleDefinition::Set(const void* Data)
{
	Val = *((TArray<UScheduleDefinition*>*)Data);
	IsSet = true;
}