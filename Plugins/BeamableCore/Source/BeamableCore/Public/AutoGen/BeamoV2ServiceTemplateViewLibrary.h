#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BeamoV2ServiceTemplateView.h"

#include "BeamoV2ServiceTemplateViewLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBeamoV2ServiceTemplateViewLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="BeamoV2ServiceTemplateView To JSON String")
	static FString BeamoV2ServiceTemplateViewToJsonString(const UBeamoV2ServiceTemplateView* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BeamoV2ServiceTemplateView", meta=(DefaultToSelf="Outer", AdvancedDisplay="Id, Outer", NativeMakeFunc))
	static UBeamoV2ServiceTemplateView* Make(FOptionalString Id, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break BeamoV2ServiceTemplateView", meta=(NativeBreakFunc))
	static void Break(const UBeamoV2ServiceTemplateView* Serializable, FOptionalString& Id);
};