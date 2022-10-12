
#pragma once

#include "CoreMinimal.h"
#include "PullBeamoManifestRequestBody.h"

#include "PullBeamoManifestRequestBodyLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UPullBeamoManifestRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize PullBeamoManifestRequestBody To JSON String")
	static FString PullBeamoManifestRequestBodyToJsonString(const UPullBeamoManifestRequestBody* Serializable, const bool Pretty);		
};