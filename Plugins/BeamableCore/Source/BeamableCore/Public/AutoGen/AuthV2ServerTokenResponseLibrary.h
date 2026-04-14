#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/AuthV2ServerTokenResponse.h"

#include "AuthV2ServerTokenResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAuthV2ServerTokenResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Json", DisplayName="AuthV2ServerTokenResponse To JSON String")
	static FString AuthV2ServerTokenResponseToJsonString(const UAuthV2ServerTokenResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Make AuthV2ServerTokenResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="AccessToken, Outer", NativeMakeFunc))
	static UAuthV2ServerTokenResponse* Make(FOptionalString AccessToken, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Break AuthV2ServerTokenResponse", meta=(NativeBreakFunc))
	static void Break(const UAuthV2ServerTokenResponse* Serializable, FOptionalString& AccessToken);
};