
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBeamoBasicManifestChecksum.h"

FOptionalBeamoBasicManifestChecksum::FOptionalBeamoBasicManifestChecksum()
{
	Val = nullptr;
	IsSet = false;
}

FOptionalBeamoBasicManifestChecksum::FOptionalBeamoBasicManifestChecksum(UBeamoBasicManifestChecksum* Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalBeamoBasicManifestChecksum::GetAddr() const { return &Val; }

void FOptionalBeamoBasicManifestChecksum::Set(const void* Data)
{
	Val = *((UBeamoBasicManifestChecksum**)Data);
	IsSet = true;
}