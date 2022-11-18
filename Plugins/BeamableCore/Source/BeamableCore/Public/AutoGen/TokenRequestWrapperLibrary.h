
#pragma once

#include "CoreMinimal.h"
#include "AutoGen/TokenRequestWrapper.h"

#include "TokenRequestWrapperLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UTokenRequestWrapperLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - TokenRequestWrapper To JSON String")
	static FString TokenRequestWrapperToJsonString(const UTokenRequestWrapper* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make TokenRequestWrapper", meta=(DefaultToSelf="Outer", AdvancedDisplay="bCustomerScoped, DeviceId, Username, RefreshToken, Context, ThirdParty, RedirectUri, ClientId, ChallengeSolution, ExternalToken, Code, ProviderAddress, Token, Password, Scope, Outer", NativeMakeFunc))
	static UTokenRequestWrapper* Make(FString GrantType, FOptionalBool bCustomerScoped, FOptionalString DeviceId, FOptionalString Username, FOptionalString RefreshToken, FOptionalContextInfo Context, FOptionalString ThirdParty, FOptionalString RedirectUri, FOptionalString ClientId, FOptionalChallengeSolution ChallengeSolution, FOptionalString ExternalToken, FOptionalString Code, FOptionalString ProviderAddress, FOptionalString Token, FOptionalString Password, FOptionalArrayOfString Scope, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break TokenRequestWrapper", meta=(NativeBreakFunc))
	static void Break(const UTokenRequestWrapper* Serializable, FString& GrantType, FOptionalBool& bCustomerScoped, FOptionalString& DeviceId, FOptionalString& Username, FOptionalString& RefreshToken, FOptionalContextInfo& Context, FOptionalString& ThirdParty, FOptionalString& RedirectUri, FOptionalString& ClientId, FOptionalChallengeSolution& ChallengeSolution, FOptionalString& ExternalToken, FOptionalString& Code, FOptionalString& ProviderAddress, FOptionalString& Token, FOptionalString& Password, FOptionalArrayOfString& Scope);
};