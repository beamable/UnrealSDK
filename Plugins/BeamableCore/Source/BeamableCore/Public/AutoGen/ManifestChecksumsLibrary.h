#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ManifestChecksums.h"

#include "ManifestChecksumsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UManifestChecksumsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Json", DisplayName="ManifestChecksums To JSON String")
	static FString ManifestChecksumsToJsonString(const UManifestChecksums* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Make ManifestChecksums", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UManifestChecksums* Make(TArray<UContentBasicManifestChecksum*> Manifests, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Break ManifestChecksums", meta=(NativeBreakFunc))
	static void Break(const UManifestChecksums* Serializable, TArray<UContentBasicManifestChecksum*>& Manifests);
};