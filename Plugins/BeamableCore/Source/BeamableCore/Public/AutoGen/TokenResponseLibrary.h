
#pragma once

#include "CoreMinimal.h"
#include "AutoGen/TokenResponse.h"

#include "TokenResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UTokenResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - TokenResponse To JSON String")
	static FString TokenResponseToJsonString(const UTokenResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make TokenResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Scopes, Outer", NativeMakeFunc))
	static UTokenResponse* Make(FString AccessToken, int64 ExpiresIn, FString RefreshToken, FString TokenType, FOptionalArrayOfString Scopes, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break TokenResponse", meta=(NativeBreakFunc))
	static void Break(const UTokenResponse* Serializable, FString& AccessToken, int64& ExpiresIn, FString& RefreshToken, FString& TokenType, FOptionalArrayOfString& Scopes);
};