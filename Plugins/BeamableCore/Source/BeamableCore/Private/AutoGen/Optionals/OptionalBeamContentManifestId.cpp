
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBeamContentManifestId.h"

FOptionalBeamContentManifestId::FOptionalBeamContentManifestId()
{
	Val = FBeamContentManifestId();
	IsSet = false;
}

FOptionalBeamContentManifestId::FOptionalBeamContentManifestId(FBeamContentManifestId Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalBeamContentManifestId::GetAddr() const { return &Val; }

void FOptionalBeamContentManifestId::Set(const void* Data)
{
	Val = *((FBeamContentManifestId*)Data);
	IsSet = true;
}