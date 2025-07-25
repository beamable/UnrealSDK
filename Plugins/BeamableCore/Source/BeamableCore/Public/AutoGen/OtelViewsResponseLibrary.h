#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/OtelViewsResponse.h"

#include "OtelViewsResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UOtelViewsResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|BeamoOtel|Utils|Json", DisplayName="OtelViewsResponse To JSON String")
	static FString OtelViewsResponseToJsonString(const UOtelViewsResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|BeamoOtel|Utils|Make/Break", DisplayName="Make OtelViewsResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UOtelViewsResponse* Make(TArray<UOtelView*> Views, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|BeamoOtel|Utils|Make/Break", DisplayName="Break OtelViewsResponse", meta=(NativeBreakFunc))
	static void Break(const UOtelViewsResponse* Serializable, TArray<UOtelView*>& Views);
};