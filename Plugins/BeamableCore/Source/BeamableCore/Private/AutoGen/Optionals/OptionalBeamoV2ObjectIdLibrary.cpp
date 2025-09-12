

#include "AutoGen/Optionals/OptionalBeamoV2ObjectIdLibrary.h"

FOptionalBeamoV2ObjectId UOptionalBeamoV2ObjectIdLibrary::MakeOptional(UBeamoV2ObjectId* Value)
{
	FOptionalBeamoV2ObjectId Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalBeamoV2ObjectId UOptionalBeamoV2ObjectIdLibrary::Conv_OptionalFromValue(UBeamoV2ObjectId* Value)
{
	FOptionalBeamoV2ObjectId Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalBeamoV2ObjectIdLibrary::HasValue(const FOptionalBeamoV2ObjectId& Optional, UBeamoV2ObjectId*& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

UBeamoV2ObjectId* UOptionalBeamoV2ObjectIdLibrary::GetOptionalValue(const FOptionalBeamoV2ObjectId& Optional, UBeamoV2ObjectId* DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

