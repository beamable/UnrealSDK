#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetManifestDiffsResponse.h"

#include "GetManifestDiffsResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetManifestDiffsResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Json", DisplayName="GetManifestDiffsResponse To JSON String")
	static FString GetManifestDiffsResponseToJsonString(const UGetManifestDiffsResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Make GetManifestDiffsResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UGetManifestDiffsResponse* Make(bool bHasMore, FString ManifestId, int32 TotalCount, TArray<UManifestDiffSummary*> Diffs, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Break GetManifestDiffsResponse", meta=(NativeBreakFunc))
	static void Break(const UGetManifestDiffsResponse* Serializable, bool& bHasMore, FString& ManifestId, int32& TotalCount, TArray<UManifestDiffSummary*>& Diffs);
};