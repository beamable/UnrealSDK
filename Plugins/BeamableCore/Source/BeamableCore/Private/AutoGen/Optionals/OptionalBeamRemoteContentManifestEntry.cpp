
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBeamRemoteContentManifestEntry.h"

FOptionalBeamRemoteContentManifestEntry::FOptionalBeamRemoteContentManifestEntry()
{
	Val = FBeamRemoteContentManifestEntry();
	IsSet = false;
}

FOptionalBeamRemoteContentManifestEntry::FOptionalBeamRemoteContentManifestEntry(FBeamRemoteContentManifestEntry Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalBeamRemoteContentManifestEntry::GetAddr() const { return &Val; }

void FOptionalBeamRemoteContentManifestEntry::Set(const void* Data)
{
	Val = *((FBeamRemoteContentManifestEntry*)Data);
	IsSet = true;
}