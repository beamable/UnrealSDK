

#include "OptionalArrayOfScheduleDefinitionLibrary.h"

FOptionalArrayOfScheduleDefinition UOptionalArrayOfScheduleDefinitionLibrary::MakeOptionalArrayOfScheduleDefinition(TArray<UScheduleDefinition*> Value)
{
	FOptionalArrayOfScheduleDefinition Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfScheduleDefinition UOptionalArrayOfScheduleDefinitionLibrary::Conv_OptionalArrayOfScheduleDefinitionFromValue(TArray<UScheduleDefinition*> Value)
{
	FOptionalArrayOfScheduleDefinition Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

