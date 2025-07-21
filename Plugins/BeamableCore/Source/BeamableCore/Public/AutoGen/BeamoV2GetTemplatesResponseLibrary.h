#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BeamoV2GetTemplatesResponse.h"

#include "BeamoV2GetTemplatesResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBeamoV2GetTemplatesResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="BeamoV2GetTemplatesResponse To JSON String")
	static FString BeamoV2GetTemplatesResponseToJsonString(const UBeamoV2GetTemplatesResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BeamoV2GetTemplatesResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Templates, Outer", NativeMakeFunc))
	static UBeamoV2GetTemplatesResponse* Make(FOptionalArrayOfBeamoV2ServiceTemplateView Templates, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break BeamoV2GetTemplatesResponse", meta=(NativeBreakFunc))
	static void Break(const UBeamoV2GetTemplatesResponse* Serializable, FOptionalArrayOfBeamoV2ServiceTemplateView& Templates);
};