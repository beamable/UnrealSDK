

#include "AutoGen/Optionals/OptionalArrayOfBeamoV2ServiceTemplateViewLibrary.h"

FOptionalArrayOfBeamoV2ServiceTemplateView UOptionalArrayOfBeamoV2ServiceTemplateViewLibrary::MakeOptional(TArray<UBeamoV2ServiceTemplateView*> Value)
{
	FOptionalArrayOfBeamoV2ServiceTemplateView Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfBeamoV2ServiceTemplateView UOptionalArrayOfBeamoV2ServiceTemplateViewLibrary::Conv_OptionalFromValue(TArray<UBeamoV2ServiceTemplateView*> Value)
{
	FOptionalArrayOfBeamoV2ServiceTemplateView Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfBeamoV2ServiceTemplateViewLibrary::HasValue(const FOptionalArrayOfBeamoV2ServiceTemplateView& Optional, TArray<UBeamoV2ServiceTemplateView*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UBeamoV2ServiceTemplateView*> UOptionalArrayOfBeamoV2ServiceTemplateViewLibrary::GetOptionalValue(const FOptionalArrayOfBeamoV2ServiceTemplateView& Optional, TArray<UBeamoV2ServiceTemplateView*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

