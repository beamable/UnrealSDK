

#include "AutoGen/Optionals/OptionalArrayOfBeamoActorServiceReferenceLibrary.h"

FOptionalArrayOfBeamoActorServiceReference UOptionalArrayOfBeamoActorServiceReferenceLibrary::MakeOptional(TArray<UBeamoActorServiceReference*> Value)
{
	FOptionalArrayOfBeamoActorServiceReference Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfBeamoActorServiceReference UOptionalArrayOfBeamoActorServiceReferenceLibrary::Conv_OptionalFromValue(TArray<UBeamoActorServiceReference*> Value)
{
	FOptionalArrayOfBeamoActorServiceReference Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfBeamoActorServiceReferenceLibrary::HasValue(const FOptionalArrayOfBeamoActorServiceReference& Optional, TArray<UBeamoActorServiceReference*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UBeamoActorServiceReference*> UOptionalArrayOfBeamoActorServiceReferenceLibrary::GetOptionalValue(const FOptionalArrayOfBeamoActorServiceReference& Optional, TArray<UBeamoActorServiceReference*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

