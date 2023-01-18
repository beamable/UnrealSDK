

#include "AutoGen/Optionals/OptionalBeamoBasicManifestChecksumLibrary.h"

FOptionalBeamoBasicManifestChecksum UOptionalBeamoBasicManifestChecksumLibrary::MakeOptional(UBeamoBasicManifestChecksum* Value)
{
	FOptionalBeamoBasicManifestChecksum Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalBeamoBasicManifestChecksum UOptionalBeamoBasicManifestChecksumLibrary::Conv_OptionalFromValue(UBeamoBasicManifestChecksum* Value)
{
	FOptionalBeamoBasicManifestChecksum Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalBeamoBasicManifestChecksumLibrary::HasValue(const FOptionalBeamoBasicManifestChecksum& Optional, UBeamoBasicManifestChecksum*& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

UBeamoBasicManifestChecksum* UOptionalBeamoBasicManifestChecksumLibrary::GetOptionalValue(const FOptionalBeamoBasicManifestChecksum& Optional, UBeamoBasicManifestChecksum* DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

