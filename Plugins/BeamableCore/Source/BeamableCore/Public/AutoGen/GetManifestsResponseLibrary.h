#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetManifestsResponse.h"

#include "GetManifestsResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetManifestsResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Json", DisplayName="GetManifestsResponse To JSON String")
	static FString GetManifestsResponseToJsonString(const UGetManifestsResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Make GetManifestsResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UGetManifestsResponse* Make(TArray<UContentBasicManifest*> Manifests, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Break GetManifestsResponse", meta=(NativeBreakFunc))
	static void Break(const UGetManifestsResponse* Serializable, TArray<UContentBasicManifest*>& Manifests);
};