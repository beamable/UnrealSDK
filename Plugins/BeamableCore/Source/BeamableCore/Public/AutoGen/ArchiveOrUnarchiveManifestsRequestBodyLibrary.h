#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ArchiveOrUnarchiveManifestsRequestBody.h"

#include "ArchiveOrUnarchiveManifestsRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UArchiveOrUnarchiveManifestsRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - ArchiveOrUnarchiveManifestsRequestBody To JSON String")
	static FString ArchiveOrUnarchiveManifestsRequestBodyToJsonString(const UArchiveOrUnarchiveManifestsRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make ArchiveOrUnarchiveManifestsRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UArchiveOrUnarchiveManifestsRequestBody* Make(TArray<FBeamContentManifestId> ManifestIds, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break ArchiveOrUnarchiveManifestsRequestBody", meta=(NativeBreakFunc))
	static void Break(const UArchiveOrUnarchiveManifestsRequestBody* Serializable, TArray<FBeamContentManifestId>& ManifestIds);
};