#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetManifestHistoryResponse.h"

#include "GetManifestHistoryResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetManifestHistoryResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Json", DisplayName="GetManifestHistoryResponse To JSON String")
	static FString GetManifestHistoryResponseToJsonString(const UGetManifestHistoryResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Make GetManifestHistoryResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UGetManifestHistoryResponse* Make(TArray<UManifestSummary*> Manifests, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Break GetManifestHistoryResponse", meta=(NativeBreakFunc))
	static void Break(const UGetManifestHistoryResponse* Serializable, TArray<UManifestSummary*>& Manifests);
};