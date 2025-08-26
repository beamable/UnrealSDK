#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BeamoV2PromoteBeamoManifestRequestBody.h"

#include "BeamoV2PromoteBeamoManifestRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBeamoV2PromoteBeamoManifestRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="BeamoV2PromoteBeamoManifestRequestBody To JSON String")
	static FString BeamoV2PromoteBeamoManifestRequestBodyToJsonString(const UBeamoV2PromoteBeamoManifestRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BeamoV2PromoteBeamoManifestRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UBeamoV2PromoteBeamoManifestRequestBody* Make(FString SourceRealmId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break BeamoV2PromoteBeamoManifestRequestBody", meta=(NativeBreakFunc))
	static void Break(const UBeamoV2PromoteBeamoManifestRequestBody* Serializable, FString& SourceRealmId);
};