#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/AuthV2ContextInfo.h"

#include "AuthV2ContextInfoLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAuthV2ContextInfoLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Json", DisplayName="AuthV2ContextInfo To JSON String")
	static FString AuthV2ContextInfoToJsonString(const UAuthV2ContextInfo* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Make AuthV2ContextInfo", meta=(DefaultToSelf="Outer", AdvancedDisplay="Platform, Device, Outer", NativeMakeFunc))
	static UAuthV2ContextInfo* Make(FOptionalString Platform, FOptionalString Device, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Break AuthV2ContextInfo", meta=(NativeBreakFunc))
	static void Break(const UAuthV2ContextInfo* Serializable, FOptionalString& Platform, FOptionalString& Device);
};