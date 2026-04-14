#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/AuthV2ExternalAuthResponse.h"

#include "AuthV2ExternalAuthResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAuthV2ExternalAuthResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Json", DisplayName="AuthV2ExternalAuthResponse To JSON String")
	static FString AuthV2ExternalAuthResponseToJsonString(const UAuthV2ExternalAuthResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Make AuthV2ExternalAuthResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="bHasAccessToken, bHasChallengeToken, bHasExpiresInMs, bHasRefreshToken, AccessToken, RefreshToken, ChallengeToken, ExpiresInMs, Outer", NativeMakeFunc))
	static UAuthV2ExternalAuthResponse* Make(FOptionalBool bHasAccessToken, FOptionalBool bHasChallengeToken, FOptionalBool bHasExpiresInMs, FOptionalBool bHasRefreshToken, FOptionalString AccessToken, FOptionalString RefreshToken, FOptionalString ChallengeToken, FOptionalInt64 ExpiresInMs, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Break AuthV2ExternalAuthResponse", meta=(NativeBreakFunc))
	static void Break(const UAuthV2ExternalAuthResponse* Serializable, FOptionalBool& bHasAccessToken, FOptionalBool& bHasChallengeToken, FOptionalBool& bHasExpiresInMs, FOptionalBool& bHasRefreshToken, FOptionalString& AccessToken, FOptionalString& RefreshToken, FOptionalString& ChallengeToken, FOptionalInt64& ExpiresInMs);
};