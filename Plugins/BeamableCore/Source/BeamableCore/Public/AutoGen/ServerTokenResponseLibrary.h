#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ServerTokenResponse.h"

#include "ServerTokenResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UServerTokenResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - ServerTokenResponse To JSON String")
	static FString ServerTokenResponseToJsonString(const UServerTokenResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make ServerTokenResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="AccessToken, Outer", NativeMakeFunc))
	static UServerTokenResponse* Make(FOptionalString AccessToken, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break ServerTokenResponse", meta=(NativeBreakFunc))
	static void Break(const UServerTokenResponse* Serializable, FOptionalString& AccessToken);
};