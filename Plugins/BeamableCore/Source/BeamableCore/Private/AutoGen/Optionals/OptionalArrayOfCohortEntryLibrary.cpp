

#include "AutoGen/Optionals/OptionalArrayOfCohortEntryLibrary.h"

FOptionalArrayOfCohortEntry UOptionalArrayOfCohortEntryLibrary::MakeOptional(TArray<UCohortEntry*> Value)
{
	FOptionalArrayOfCohortEntry Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfCohortEntry UOptionalArrayOfCohortEntryLibrary::Conv_OptionalFromValue(TArray<UCohortEntry*> Value)
{
	FOptionalArrayOfCohortEntry Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfCohortEntryLibrary::HasValue(const FOptionalArrayOfCohortEntry& Optional, TArray<UCohortEntry*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UCohortEntry*> UOptionalArrayOfCohortEntryLibrary::GetOptionalValue(const FOptionalArrayOfCohortEntry& Optional, TArray<UCohortEntry*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

