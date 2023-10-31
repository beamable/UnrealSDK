#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/CloudsavingBasicManifest.h"

#include "CloudsavingBasicManifestLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCloudsavingBasicManifestLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - CloudsavingBasicManifest To JSON String")
	static FString CloudsavingBasicManifestToJsonString(const UCloudsavingBasicManifest* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make CloudsavingBasicManifest", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UCloudsavingBasicManifest* Make(bool bReplacement, FString Id, int64 Created, TArray<UCloudsavingBasicReference*> Manifest, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break CloudsavingBasicManifest", meta=(NativeBreakFunc))
	static void Break(const UCloudsavingBasicManifest* Serializable, bool& bReplacement, FString& Id, int64& Created, TArray<UCloudsavingBasicReference*>& Manifest);
};