#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/StartSessionRequestBody.h"

#include "StartSessionRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UStartSessionRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Session|Utils|Json", DisplayName="StartSessionRequestBody To JSON String")
	static FString StartSessionRequestBodyToJsonString(const UStartSessionRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Session|Utils|Make/Break", DisplayName="Make StartSessionRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Source, Shard, Locale, Language, Time, Platform, Gamer, Device, CustomParams, DeviceParams, Outer", NativeMakeFunc))
	static UStartSessionRequestBody* Make(FOptionalString Source, FOptionalString Shard, FOptionalString Locale, FOptionalSessionLanguageContext Language, FOptionalInt64 Time, FOptionalString Platform, FOptionalInt64 Gamer, FOptionalString Device, FOptionalMapOfString CustomParams, FOptionalMapOfString DeviceParams, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Session|Utils|Make/Break", DisplayName="Break StartSessionRequestBody", meta=(NativeBreakFunc))
	static void Break(const UStartSessionRequestBody* Serializable, FOptionalString& Source, FOptionalString& Shard, FOptionalString& Locale, FOptionalSessionLanguageContext& Language, FOptionalInt64& Time, FOptionalString& Platform, FOptionalInt64& Gamer, FOptionalString& Device, FOptionalMapOfString& CustomParams, FOptionalMapOfString& DeviceParams);
};