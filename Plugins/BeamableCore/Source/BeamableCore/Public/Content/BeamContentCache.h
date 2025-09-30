#pragma once

#include "BeamContentObject.h"
#include "BeamCoreSettings.h"
#include "BeamBackend/ReplacementTypes/BeamRemoteContentManifestEntry.h"
#include "BeamBackend/SemanticTypes/BeamContentId.h"
#include "BeamBackend/SemanticTypes/BeamContentManifestId.h"
#include "Engine/DataTable.h"

#include "BeamContentCache.generated.h"

class UBeamContentCacheSerializer;
struct FBeamContentCacheSerializationContext;


UCLASS(BlueprintType)
class BEAMABLECORE_API UBeamContentCache : public UObject
{
	GENERATED_BODY()

	friend class UBeamContentSubsystem;

public:	
	static FString CACHE_FOLDER() { return FPaths::ProjectSavedDir() / "Beamable" / "ContentCache"; };
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FBeamContentManifestId ManifestId;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TMap<FBeamContentId, UBeamContentObject*> Cache;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TMap<FBeamContentId, FString> Hashes;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TArray<FBeamRemoteContentManifestEntry> LatestRemoteManifest;


	bool SerializeToBinary(FBeamContentCacheSerializationContext& Ctx, UBeamContentCacheSerializer* HeaderSerializer);
};
