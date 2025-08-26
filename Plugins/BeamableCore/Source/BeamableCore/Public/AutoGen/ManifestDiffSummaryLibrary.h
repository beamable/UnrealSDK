#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ManifestDiffSummary.h"

#include "ManifestDiffSummaryLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UManifestDiffSummaryLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Json", DisplayName="ManifestDiffSummary To JSON String")
	static FString ManifestDiffSummaryToJsonString(const UManifestDiffSummary* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Make ManifestDiffSummary", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UManifestDiffSummary* Make(FString ManifestUid, FString DiffUrl, int64 CreatedDate, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Break ManifestDiffSummary", meta=(NativeBreakFunc))
	static void Break(const UManifestDiffSummary* Serializable, FString& ManifestUid, FString& DiffUrl, int64& CreatedDate);
};