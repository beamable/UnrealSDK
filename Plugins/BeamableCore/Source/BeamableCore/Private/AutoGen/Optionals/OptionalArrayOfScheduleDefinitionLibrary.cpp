

#include "AutoGen/Optionals/OptionalArrayOfScheduleDefinitionLibrary.h"

FOptionalArrayOfScheduleDefinition UOptionalArrayOfScheduleDefinitionLibrary::MakeOptional(TArray<UScheduleDefinition*> Value)
{
	FOptionalArrayOfScheduleDefinition Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfScheduleDefinition UOptionalArrayOfScheduleDefinitionLibrary::Conv_OptionalFromValue(TArray<UScheduleDefinition*> Value)
{
	FOptionalArrayOfScheduleDefinition Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfScheduleDefinitionLibrary::HasValue(const FOptionalArrayOfScheduleDefinition& Optional, TArray<UScheduleDefinition*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UScheduleDefinition*> UOptionalArrayOfScheduleDefinitionLibrary::GetOptionalValue(const FOptionalArrayOfScheduleDefinition& Optional, TArray<UScheduleDefinition*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

