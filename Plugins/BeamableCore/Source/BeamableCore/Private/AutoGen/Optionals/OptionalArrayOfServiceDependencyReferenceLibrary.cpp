

#include "AutoGen/Optionals/OptionalArrayOfServiceDependencyReferenceLibrary.h"

FOptionalArrayOfServiceDependencyReference UOptionalArrayOfServiceDependencyReferenceLibrary::MakeOptional(TArray<UServiceDependencyReference*> Value)
{
	FOptionalArrayOfServiceDependencyReference Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfServiceDependencyReference UOptionalArrayOfServiceDependencyReferenceLibrary::Conv_OptionalFromValue(TArray<UServiceDependencyReference*> Value)
{
	FOptionalArrayOfServiceDependencyReference Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfServiceDependencyReferenceLibrary::HasValue(const FOptionalArrayOfServiceDependencyReference& Optional, TArray<UServiceDependencyReference*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UServiceDependencyReference*> UOptionalArrayOfServiceDependencyReferenceLibrary::GetOptionalValue(const FOptionalArrayOfServiceDependencyReference& Optional, TArray<UServiceDependencyReference*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

