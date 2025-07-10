#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/OtelAuthConfig.h"

#include "OtelAuthConfigLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UOtelAuthConfigLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|BeamoOtel|Utils|Json", DisplayName="OtelAuthConfig To JSON String")
	static FString OtelAuthConfigToJsonString(const UOtelAuthConfig* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|BeamoOtel|Utils|Make/Break", DisplayName="Make OtelAuthConfig", meta=(DefaultToSelf="Outer", AdvancedDisplay="ExpiresAt, Outer", NativeMakeFunc))
	static UOtelAuthConfig* Make(FString Endpoint, FString Username, FString Password, FOptionalDateTime ExpiresAt, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|BeamoOtel|Utils|Make/Break", DisplayName="Break OtelAuthConfig", meta=(NativeBreakFunc))
	static void Break(const UOtelAuthConfig* Serializable, FString& Endpoint, FString& Username, FString& Password, FOptionalDateTime& ExpiresAt);
};