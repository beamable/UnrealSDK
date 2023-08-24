#pragma once

#include "AutoGen/Optionals/OptionalString.h"
#include "BeamBackend/BeamBackend.h"
#include "BeamBackend/SemanticTypes/BeamContentId.h"
#include "BeamBackend/SemanticTypes/BeamContentManifestId.h"

#include "DownloadContentState.generated.h"

USTRUCT()
struct BEAMABLECORE_API FDownloadContentState
{
	GENERATED_BODY()
	
	FBeamContentManifestId ManifestId;
	FBeamContentId Id;
	TArray<FString> Tags;
	FOptionalString Checksum;
	TUnrealRequestPtr Request;
};
