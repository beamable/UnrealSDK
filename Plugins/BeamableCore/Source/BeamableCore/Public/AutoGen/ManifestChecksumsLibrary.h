
#pragma once

#include "CoreMinimal.h"
#include "AutoGen/ManifestChecksums.h"

#include "ManifestChecksumsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UManifestChecksumsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - ManifestChecksums To JSON String")
	static FString ManifestChecksumsToJsonString(const UManifestChecksums* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make ManifestChecksums", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UManifestChecksums* Make(TArray<UManifestChecksum*> Manifests, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break ManifestChecksums", meta=(NativeBreakFunc))
	static void Break(const UManifestChecksums* Serializable, TArray<UManifestChecksum*>& Manifests);
};