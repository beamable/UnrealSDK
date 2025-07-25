#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BeamoV2QueryResponse.h"

#include "BeamoV2QueryResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBeamoV2QueryResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="BeamoV2QueryResponse To JSON String")
	static FString BeamoV2QueryResponseToJsonString(const UBeamoV2QueryResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BeamoV2QueryResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="QueryId, Outer", NativeMakeFunc))
	static UBeamoV2QueryResponse* Make(FOptionalString QueryId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break BeamoV2QueryResponse", meta=(NativeBreakFunc))
	static void Break(const UBeamoV2QueryResponse* Serializable, FOptionalString& QueryId);
};