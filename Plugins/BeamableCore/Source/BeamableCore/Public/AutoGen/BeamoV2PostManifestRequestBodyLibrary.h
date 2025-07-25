#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BeamoV2PostManifestRequestBody.h"

#include "BeamoV2PostManifestRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBeamoV2PostManifestRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="BeamoV2PostManifestRequestBody To JSON String")
	static FString BeamoV2PostManifestRequestBodyToJsonString(const UBeamoV2PostManifestRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BeamoV2PostManifestRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="bAutoDeploy, Comments, Manifest, StorageReferences, Outer", NativeMakeFunc))
	static UBeamoV2PostManifestRequestBody* Make(FOptionalBool bAutoDeploy, FOptionalString Comments, FOptionalArrayOfBeamoV2ServiceReference Manifest, FOptionalArrayOfBeamoV2ServiceStorageReference StorageReferences, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break BeamoV2PostManifestRequestBody", meta=(NativeBreakFunc))
	static void Break(const UBeamoV2PostManifestRequestBody* Serializable, FOptionalBool& bAutoDeploy, FOptionalString& Comments, FOptionalArrayOfBeamoV2ServiceReference& Manifest, FOptionalArrayOfBeamoV2ServiceStorageReference& StorageReferences);
};