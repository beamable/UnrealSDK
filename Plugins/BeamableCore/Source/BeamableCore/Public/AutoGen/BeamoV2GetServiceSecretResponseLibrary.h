#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BeamoV2GetServiceSecretResponse.h"

#include "BeamoV2GetServiceSecretResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBeamoV2GetServiceSecretResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="BeamoV2GetServiceSecretResponse To JSON String")
	static FString BeamoV2GetServiceSecretResponseToJsonString(const UBeamoV2GetServiceSecretResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BeamoV2GetServiceSecretResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Secret, Outer", NativeMakeFunc))
	static UBeamoV2GetServiceSecretResponse* Make(FOptionalString Secret, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break BeamoV2GetServiceSecretResponse", meta=(NativeBreakFunc))
	static void Break(const UBeamoV2GetServiceSecretResponse* Serializable, FOptionalString& Secret);
};