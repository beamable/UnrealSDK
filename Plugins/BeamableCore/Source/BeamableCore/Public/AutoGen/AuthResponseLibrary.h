#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/AuthResponse.h"

#include "AuthResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAuthResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Json", DisplayName="AuthResponse To JSON String")
	static FString AuthResponseToJsonString(const UAuthResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Make AuthResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="AccessToken, RefreshToken, Outer", NativeMakeFunc))
	static UAuthResponse* Make(FOptionalString AccessToken, FOptionalString RefreshToken, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Break AuthResponse", meta=(NativeBreakFunc))
	static void Break(const UAuthResponse* Serializable, FOptionalString& AccessToken, FOptionalString& RefreshToken);
};