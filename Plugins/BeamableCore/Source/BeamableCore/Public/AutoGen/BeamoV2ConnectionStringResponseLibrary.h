#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BeamoV2ConnectionStringResponse.h"

#include "BeamoV2ConnectionStringResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBeamoV2ConnectionStringResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="BeamoV2ConnectionStringResponse To JSON String")
	static FString BeamoV2ConnectionStringResponseToJsonString(const UBeamoV2ConnectionStringResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BeamoV2ConnectionStringResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="ConnectionString, Outer", NativeMakeFunc))
	static UBeamoV2ConnectionStringResponse* Make(FOptionalString ConnectionString, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break BeamoV2ConnectionStringResponse", meta=(NativeBreakFunc))
	static void Break(const UBeamoV2ConnectionStringResponse* Serializable, FOptionalString& ConnectionString);
};