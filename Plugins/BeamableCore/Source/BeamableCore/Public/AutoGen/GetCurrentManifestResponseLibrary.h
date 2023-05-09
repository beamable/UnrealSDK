#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetCurrentManifestResponse.h"

#include "GetCurrentManifestResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetCurrentManifestResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - GetCurrentManifestResponse To JSON String")
	static FString GetCurrentManifestResponseToJsonString(const UGetCurrentManifestResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make GetCurrentManifestResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UGetCurrentManifestResponse* Make(UManifestView* Manifest, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break GetCurrentManifestResponse", meta=(NativeBreakFunc))
	static void Break(const UGetCurrentManifestResponse* Serializable, UManifestView*& Manifest);
};