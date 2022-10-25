
#include "AutoGen/Optionals/OptionalManifestChecksum.h"

FOptionalManifestChecksum::FOptionalManifestChecksum()
{
	Val = nullptr;
	IsSet = false;
}

FOptionalManifestChecksum::FOptionalManifestChecksum(UManifestChecksum* Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalManifestChecksum::GetAddr() const { return &Val; }

void FOptionalManifestChecksum::Set(const void* Data)
{
	Val = *((UManifestChecksum**)Data);
	IsSet = true;
}