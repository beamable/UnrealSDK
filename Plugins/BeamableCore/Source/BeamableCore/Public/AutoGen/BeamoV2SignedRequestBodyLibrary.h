#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BeamoV2SignedRequestBody.h"

#include "BeamoV2SignedRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBeamoV2SignedRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="BeamoV2SignedRequestBody To JSON String")
	static FString BeamoV2SignedRequestBodyToJsonString(const UBeamoV2SignedRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BeamoV2SignedRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Url, Body, Method, Headers, Outer", NativeMakeFunc))
	static UBeamoV2SignedRequestBody* Make(FOptionalString Url, FOptionalString Body, FOptionalString Method, FOptionalArrayOfBeamoV2StringStringKeyValuePair Headers, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break BeamoV2SignedRequestBody", meta=(NativeBreakFunc))
	static void Break(const UBeamoV2SignedRequestBody* Serializable, FOptionalString& Url, FOptionalString& Body, FOptionalString& Method, FOptionalArrayOfBeamoV2StringStringKeyValuePair& Headers);
};