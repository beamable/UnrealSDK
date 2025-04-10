#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/PullBeamoManifestRequestBody.h"

#include "PullBeamoManifestRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPullBeamoManifestRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|4 - Json", DisplayName="PullBeamoManifestRequestBody To JSON String")
	static FString PullBeamoManifestRequestBodyToJsonString(const UPullBeamoManifestRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|3 - Backend", DisplayName="Make PullBeamoManifestRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UPullBeamoManifestRequestBody* Make(FString SourceRealmPid, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|3 - Backend", DisplayName="Break PullBeamoManifestRequestBody", meta=(NativeBreakFunc))
	static void Break(const UPullBeamoManifestRequestBody* Serializable, FString& SourceRealmPid);
};