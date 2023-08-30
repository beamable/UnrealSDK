#pragma once

#include "BeamContentObject.h"
#include "BeamBackend/SemanticTypes/BeamContentId.h"
#include "BeamBackend/SemanticTypes/BeamContentManifestId.h"
#include "Engine/DataTable.h"

#include "BeamContentCache.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UBeamContentCache : public UObject
{
	GENERATED_BODY()

	friend class UBeamContentSubsystem;

public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FBeamContentManifestId ManifestId;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TMap<FBeamContentId, UBeamContentObject*> Cache;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TMap<FBeamContentId, FString> Hashes;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UDataTable* LatestRemoteManifest;
};
