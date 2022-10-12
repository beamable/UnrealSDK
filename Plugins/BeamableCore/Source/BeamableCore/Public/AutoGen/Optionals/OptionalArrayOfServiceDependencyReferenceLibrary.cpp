

#include "OptionalArrayOfServiceDependencyReferenceLibrary.h"

FOptionalArrayOfServiceDependencyReference UOptionalArrayOfServiceDependencyReferenceLibrary::MakeOptionalArrayOfServiceDependencyReference(TArray<UServiceDependencyReference*> Value)
{
	FOptionalArrayOfServiceDependencyReference Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfServiceDependencyReference UOptionalArrayOfServiceDependencyReferenceLibrary::Conv_OptionalArrayOfServiceDependencyReferenceFromValue(TArray<UServiceDependencyReference*> Value)
{
	FOptionalArrayOfServiceDependencyReference Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

