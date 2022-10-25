
#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Manifest.h"

#include "ManifestLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UManifestLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - Manifest To JSON String")
	static FString ManifestToJsonString(const UManifest* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make Manifest", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UManifest* Make(bool bReplacement, FString Id, int64 Created, TArray<UReference*> Manifest, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break Manifest", meta=(NativeBreakFunc))
	static void Break(const UManifest* Serializable, bool& bReplacement, FString& Id, int64& Created, TArray<UReference*>& Manifest);
};