#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ManifestSummary.h"

#include "ManifestSummaryLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UManifestSummaryLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Content|4 - Json", DisplayName="ManifestSummary To JSON String")
	static FString ManifestSummaryToJsonString(const UManifestSummary* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Content|3 - Backend", DisplayName="Make ManifestSummary", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UManifestSummary* Make(FString Uid, UContentBasicManifestChecksum* Manifest, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Content|3 - Backend", DisplayName="Break ManifestSummary", meta=(NativeBreakFunc))
	static void Break(const UManifestSummary* Serializable, FString& Uid, UContentBasicManifestChecksum*& Manifest);
};