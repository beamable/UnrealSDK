#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ServiceImageLayers.h"

#include "ServiceImageLayersLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UServiceImageLayersLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - ServiceImageLayers To JSON String")
	static FString ServiceImageLayersToJsonString(const UServiceImageLayers* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make ServiceImageLayers", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UServiceImageLayers* Make(UBeamoBasicReference* Service, TArray<FString> Layers, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break ServiceImageLayers", meta=(NativeBreakFunc))
	static void Break(const UServiceImageLayers* Serializable, UBeamoBasicReference*& Service, TArray<FString>& Layers);
};