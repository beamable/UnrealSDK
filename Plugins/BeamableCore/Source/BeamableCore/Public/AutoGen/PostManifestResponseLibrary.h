#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BeamableCore/Public/AutoGen/PostManifestResponse.h"

#include "PostManifestResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPostManifestResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - PostManifestResponse To JSON String")
	static FString PostManifestResponseToJsonString(const UPostManifestResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make PostManifestResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Manifest, Outer", NativeMakeFunc))
	static UPostManifestResponse* Make(FOptionalBeamoBasicManifestChecksum Manifest, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break PostManifestResponse", meta=(NativeBreakFunc))
	static void Break(const UPostManifestResponse* Serializable, FOptionalBeamoBasicManifestChecksum& Manifest);
};