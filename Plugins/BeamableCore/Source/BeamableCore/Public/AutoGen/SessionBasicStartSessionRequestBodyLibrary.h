#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/SessionBasicStartSessionRequestBody.h"

#include "SessionBasicStartSessionRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API USessionBasicStartSessionRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Session|Utils|Json", DisplayName="SessionBasicStartSessionRequestBody To JSON String")
	static FString SessionBasicStartSessionRequestBodyToJsonString(const USessionBasicStartSessionRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Session|Utils|Make/Break", DisplayName="Make SessionBasicStartSessionRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Source, Shard, Locale, Language, Time, Platform, Gamer, Device, CustomParams, DeviceParams, Outer", NativeMakeFunc))
	static USessionBasicStartSessionRequestBody* Make(FOptionalString Source, FOptionalString Shard, FOptionalString Locale, FOptionalSessionLanguageContext Language, FOptionalInt64 Time, FOptionalString Platform, FOptionalInt64 Gamer, FOptionalString Device, FOptionalMapOfString CustomParams, FOptionalMapOfString DeviceParams, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Session|Utils|Make/Break", DisplayName="Break SessionBasicStartSessionRequestBody", meta=(NativeBreakFunc))
	static void Break(const USessionBasicStartSessionRequestBody* Serializable, FOptionalString& Source, FOptionalString& Shard, FOptionalString& Locale, FOptionalSessionLanguageContext& Language, FOptionalInt64& Time, FOptionalString& Platform, FOptionalInt64& Gamer, FOptionalString& Device, FOptionalMapOfString& CustomParams, FOptionalMapOfString& DeviceParams);
};