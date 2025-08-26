#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BeamoV2UriResponse.h"

#include "BeamoV2UriResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBeamoV2UriResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="BeamoV2UriResponse To JSON String")
	static FString BeamoV2UriResponseToJsonString(const UBeamoV2UriResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BeamoV2UriResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Uri, Outer", NativeMakeFunc))
	static UBeamoV2UriResponse* Make(FOptionalString Uri, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break BeamoV2UriResponse", meta=(NativeBreakFunc))
	static void Break(const UBeamoV2UriResponse* Serializable, FOptionalString& Uri);
};