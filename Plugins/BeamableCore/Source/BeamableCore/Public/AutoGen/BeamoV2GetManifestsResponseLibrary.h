#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BeamoV2GetManifestsResponse.h"

#include "BeamoV2GetManifestsResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBeamoV2GetManifestsResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="BeamoV2GetManifestsResponse To JSON String")
	static FString BeamoV2GetManifestsResponseToJsonString(const UBeamoV2GetManifestsResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BeamoV2GetManifestsResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Manifests, Outer", NativeMakeFunc))
	static UBeamoV2GetManifestsResponse* Make(FOptionalArrayOfBeamoV2Manifest Manifests, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break BeamoV2GetManifestsResponse", meta=(NativeBreakFunc))
	static void Break(const UBeamoV2GetManifestsResponse* Serializable, FOptionalArrayOfBeamoV2Manifest& Manifests);
};