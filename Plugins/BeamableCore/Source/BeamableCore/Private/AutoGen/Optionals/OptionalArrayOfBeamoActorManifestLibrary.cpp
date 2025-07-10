

#include "AutoGen/Optionals/OptionalArrayOfBeamoActorManifestLibrary.h"

FOptionalArrayOfBeamoActorManifest UOptionalArrayOfBeamoActorManifestLibrary::MakeOptional(TArray<UBeamoActorManifest*> Value)
{
	FOptionalArrayOfBeamoActorManifest Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfBeamoActorManifest UOptionalArrayOfBeamoActorManifestLibrary::Conv_OptionalFromValue(TArray<UBeamoActorManifest*> Value)
{
	FOptionalArrayOfBeamoActorManifest Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfBeamoActorManifestLibrary::HasValue(const FOptionalArrayOfBeamoActorManifest& Optional, TArray<UBeamoActorManifest*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UBeamoActorManifest*> UOptionalArrayOfBeamoActorManifestLibrary::GetOptionalValue(const FOptionalArrayOfBeamoActorManifest& Optional, TArray<UBeamoActorManifest*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

