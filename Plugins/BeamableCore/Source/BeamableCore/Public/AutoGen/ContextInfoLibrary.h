#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ContextInfo.h"

#include "ContextInfoLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UContextInfoLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - ContextInfo To JSON String")
	static FString ContextInfoToJsonString(const UContextInfo* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make ContextInfo", meta=(DefaultToSelf="Outer", AdvancedDisplay="Platform, Device, Outer", NativeMakeFunc))
	static UContextInfo* Make(FOptionalString Platform, FOptionalString Device, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break ContextInfo", meta=(NativeBreakFunc))
	static void Break(const UContextInfo* Serializable, FOptionalString& Platform, FOptionalString& Device);
};