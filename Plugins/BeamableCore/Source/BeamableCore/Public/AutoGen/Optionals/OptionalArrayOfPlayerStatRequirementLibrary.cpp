

#include "OptionalArrayOfPlayerStatRequirementLibrary.h"

FOptionalArrayOfPlayerStatRequirement UOptionalArrayOfPlayerStatRequirementLibrary::MakeOptionalArrayOfPlayerStatRequirement(TArray<UPlayerStatRequirement*> Value)
{
	FOptionalArrayOfPlayerStatRequirement Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfPlayerStatRequirement UOptionalArrayOfPlayerStatRequirementLibrary::Conv_OptionalArrayOfPlayerStatRequirementFromValue(TArray<UPlayerStatRequirement*> Value)
{
	FOptionalArrayOfPlayerStatRequirement Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

