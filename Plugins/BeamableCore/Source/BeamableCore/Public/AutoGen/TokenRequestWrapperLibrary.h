#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/TokenRequestWrapper.h"

#include "TokenRequestWrapperLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UTokenRequestWrapperLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - TokenRequestWrapper To JSON String")
	static FString TokenRequestWrapperToJsonString(const UTokenRequestWrapper* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make TokenRequestWrapper", meta=(DefaultToSelf="Outer", AdvancedDisplay="bCustomerScoped, DeviceId, ProviderService, Token, Code, ExternalToken, ChallengeSolution, ProviderNamespace, RedirectUri, ThirdParty, Context, RefreshToken, Username, ClientId, Password, Scope, Outer", NativeMakeFunc))
	static UTokenRequestWrapper* Make(FString GrantType, FOptionalBool bCustomerScoped, FOptionalString DeviceId, FOptionalString ProviderService, FOptionalString Token, FOptionalString Code, FOptionalString ExternalToken, FOptionalChallengeSolution ChallengeSolution, FOptionalString ProviderNamespace, FOptionalString RedirectUri, FOptionalString ThirdParty, FOptionalContextInfo Context, FOptionalString RefreshToken, FOptionalString Username, FOptionalString ClientId, FOptionalString Password, FOptionalArrayOfString Scope, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break TokenRequestWrapper", meta=(NativeBreakFunc))
	static void Break(const UTokenRequestWrapper* Serializable, FString& GrantType, FOptionalBool& bCustomerScoped, FOptionalString& DeviceId, FOptionalString& ProviderService, FOptionalString& Token, FOptionalString& Code, FOptionalString& ExternalToken, FOptionalChallengeSolution& ChallengeSolution, FOptionalString& ProviderNamespace, FOptionalString& RedirectUri, FOptionalString& ThirdParty, FOptionalContextInfo& Context, FOptionalString& RefreshToken, FOptionalString& Username, FOptionalString& ClientId, FOptionalString& Password, FOptionalArrayOfString& Scope);
};