#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/AuthV2OpenIdConfigResponse.h"

#include "AuthV2OpenIdConfigResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAuthV2OpenIdConfigResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Json", DisplayName="AuthV2OpenIdConfigResponse To JSON String")
	static FString AuthV2OpenIdConfigResponseToJsonString(const UAuthV2OpenIdConfigResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Make AuthV2OpenIdConfigResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UAuthV2OpenIdConfigResponse* Make(FString Issuer, FString JwksUri, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Break AuthV2OpenIdConfigResponse", meta=(NativeBreakFunc))
	static void Break(const UAuthV2OpenIdConfigResponse* Serializable, FString& Issuer, FString& JwksUri);
};