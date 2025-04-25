#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/PostManifestResponse.h"

#include "PostManifestResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPostManifestResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="PostManifestResponse To JSON String")
	static FString PostManifestResponseToJsonString(const UPostManifestResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make PostManifestResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Manifest, Outer", NativeMakeFunc))
	static UPostManifestResponse* Make(FOptionalBeamoBasicManifestChecksum Manifest, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break PostManifestResponse", meta=(NativeBreakFunc))
	static void Break(const UPostManifestResponse* Serializable, FOptionalBeamoBasicManifestChecksum& Manifest);
};