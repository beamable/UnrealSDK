#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BeamoBasicGetManifestRequestBody.h"

#include "BeamoBasicGetManifestRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBeamoBasicGetManifestRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="BeamoBasicGetManifestRequestBody To JSON String")
	static FString BeamoBasicGetManifestRequestBodyToJsonString(const UBeamoBasicGetManifestRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BeamoBasicGetManifestRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="bArchived, Outer", NativeMakeFunc))
	static UBeamoBasicGetManifestRequestBody* Make(FString Id, FOptionalBool bArchived, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break BeamoBasicGetManifestRequestBody", meta=(NativeBreakFunc))
	static void Break(const UBeamoBasicGetManifestRequestBody* Serializable, FString& Id, FOptionalBool& bArchived);
};