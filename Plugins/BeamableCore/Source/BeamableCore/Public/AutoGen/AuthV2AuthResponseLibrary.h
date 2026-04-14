#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/AuthV2AuthResponse.h"

#include "AuthV2AuthResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAuthV2AuthResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Json", DisplayName="AuthV2AuthResponse To JSON String")
	static FString AuthV2AuthResponseToJsonString(const UAuthV2AuthResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Make AuthV2AuthResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="AccessToken, RefreshToken, Outer", NativeMakeFunc))
	static UAuthV2AuthResponse* Make(FOptionalString AccessToken, FOptionalString RefreshToken, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Break AuthV2AuthResponse", meta=(NativeBreakFunc))
	static void Break(const UAuthV2AuthResponse* Serializable, FOptionalString& AccessToken, FOptionalString& RefreshToken);
};