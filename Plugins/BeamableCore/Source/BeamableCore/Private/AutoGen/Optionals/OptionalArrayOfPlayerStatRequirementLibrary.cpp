

#include "AutoGen/Optionals/OptionalArrayOfPlayerStatRequirementLibrary.h"

FOptionalArrayOfPlayerStatRequirement UOptionalArrayOfPlayerStatRequirementLibrary::MakeOptional(TArray<UPlayerStatRequirement*> Value)
{
	FOptionalArrayOfPlayerStatRequirement Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfPlayerStatRequirement UOptionalArrayOfPlayerStatRequirementLibrary::Conv_OptionalFromValue(TArray<UPlayerStatRequirement*> Value)
{
	FOptionalArrayOfPlayerStatRequirement Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfPlayerStatRequirementLibrary::HasValue(const FOptionalArrayOfPlayerStatRequirement& Optional, TArray<UPlayerStatRequirement*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UPlayerStatRequirement*> UOptionalArrayOfPlayerStatRequirementLibrary::GetOptionalValue(const FOptionalArrayOfPlayerStatRequirement& Optional, TArray<UPlayerStatRequirement*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

