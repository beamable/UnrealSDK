#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/SessionActorStartSessionRequestBody.h"

#include "SessionActorStartSessionRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API USessionActorStartSessionRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Session|Utils|Json", DisplayName="SessionActorStartSessionRequestBody To JSON String")
	static FString SessionActorStartSessionRequestBodyToJsonString(const USessionActorStartSessionRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Session|Utils|Make/Break", DisplayName="Make SessionActorStartSessionRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Platform, Device, Source, Locale, Language, CustomParams, Outer", NativeMakeFunc))
	static USessionActorStartSessionRequestBody* Make(FOptionalString Platform, FOptionalString Device, FOptionalString Source, FOptionalString Locale, FOptionalSessionLanguageContextDto Language, FOptionalMapOfString CustomParams, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Session|Utils|Make/Break", DisplayName="Break SessionActorStartSessionRequestBody", meta=(NativeBreakFunc))
	static void Break(const USessionActorStartSessionRequestBody* Serializable, FOptionalString& Platform, FOptionalString& Device, FOptionalString& Source, FOptionalString& Locale, FOptionalSessionLanguageContextDto& Language, FOptionalMapOfString& CustomParams);
};