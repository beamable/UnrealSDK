#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/PromoteBeamoManifestRequestBody.h"

#include "PromoteBeamoManifestRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPromoteBeamoManifestRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="PromoteBeamoManifestRequestBody To JSON String")
	static FString PromoteBeamoManifestRequestBodyToJsonString(const UPromoteBeamoManifestRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make PromoteBeamoManifestRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UPromoteBeamoManifestRequestBody* Make(FString SourceRealmId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break PromoteBeamoManifestRequestBody", meta=(NativeBreakFunc))
	static void Break(const UPromoteBeamoManifestRequestBody* Serializable, FString& SourceRealmId);
};