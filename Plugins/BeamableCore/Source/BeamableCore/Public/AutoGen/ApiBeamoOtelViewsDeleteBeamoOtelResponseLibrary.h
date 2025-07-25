#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ApiBeamoOtelViewsDeleteBeamoOtelResponse.h"

#include "ApiBeamoOtelViewsDeleteBeamoOtelResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UApiBeamoOtelViewsDeleteBeamoOtelResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|BeamoOtel|Utils|Json", DisplayName="ApiBeamoOtelViewsDeleteBeamoOtelResponse To JSON String")
	static FString ApiBeamoOtelViewsDeleteBeamoOtelResponseToJsonString(const UApiBeamoOtelViewsDeleteBeamoOtelResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|BeamoOtel|Utils|Make/Break", DisplayName="Make ApiBeamoOtelViewsDeleteBeamoOtelResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UApiBeamoOtelViewsDeleteBeamoOtelResponse* Make(UObject* Outer);

	
};