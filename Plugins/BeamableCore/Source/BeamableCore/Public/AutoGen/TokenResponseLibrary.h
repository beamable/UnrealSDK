#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/TokenResponse.h"

#include "TokenResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UTokenResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Json", DisplayName="TokenResponse To JSON String")
	static FString TokenResponseToJsonString(const UTokenResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Make TokenResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="AccessToken, RefreshToken, ChallengeToken, Scopes, Outer", NativeMakeFunc))
	static UTokenResponse* Make(int64 ExpiresIn, FString TokenType, FOptionalString AccessToken, FOptionalString RefreshToken, FOptionalString ChallengeToken, FOptionalArrayOfString Scopes, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Break TokenResponse", meta=(NativeBreakFunc))
	static void Break(const UTokenResponse* Serializable, int64& ExpiresIn, FString& TokenType, FOptionalString& AccessToken, FOptionalString& RefreshToken, FOptionalString& ChallengeToken, FOptionalArrayOfString& Scopes);
};