#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/SteamAuthRequestBody.h"

#include "SteamAuthRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API USteamAuthRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Payments|Utils|Json", DisplayName="SteamAuthRequestBody To JSON String")
	static FString SteamAuthRequestBodyToJsonString(const USteamAuthRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Payments|Utils|Make/Break", DisplayName="Make SteamAuthRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static USteamAuthRequestBody* Make(FString Ticket, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Payments|Utils|Make/Break", DisplayName="Break SteamAuthRequestBody", meta=(NativeBreakFunc))
	static void Break(const USteamAuthRequestBody* Serializable, FString& Ticket);
};