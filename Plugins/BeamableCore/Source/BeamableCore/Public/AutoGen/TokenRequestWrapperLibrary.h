#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/TokenRequestWrapper.h"

#include "TokenRequestWrapperLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UTokenRequestWrapperLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Json", DisplayName="TokenRequestWrapper To JSON String")
	static FString TokenRequestWrapperToJsonString(const UTokenRequestWrapper* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Make TokenRequestWrapper", meta=(DefaultToSelf="Outer", AdvancedDisplay="bCustomerScoped, DeviceId, ProviderService, Token, Code, ExternalToken, ChallengeSolution, ProviderNamespace, RedirectUri, ThirdParty, Context, RefreshToken, Username, ClientId, Password, Scope, InitProperties, Outer", NativeMakeFunc))
	static UTokenRequestWrapper* Make(FString GrantType, FOptionalBool bCustomerScoped, FOptionalString DeviceId, FOptionalString ProviderService, FOptionalString Token, FOptionalString Code, FOptionalString ExternalToken, FOptionalChallengeSolution ChallengeSolution, FOptionalString ProviderNamespace, FOptionalString RedirectUri, FOptionalString ThirdParty, FOptionalContextInfo Context, FOptionalString RefreshToken, FOptionalString Username, FOptionalString ClientId, FOptionalString Password, FOptionalArrayOfString Scope, FOptionalMapOfString InitProperties, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Break TokenRequestWrapper", meta=(NativeBreakFunc))
	static void Break(const UTokenRequestWrapper* Serializable, FString& GrantType, FOptionalBool& bCustomerScoped, FOptionalString& DeviceId, FOptionalString& ProviderService, FOptionalString& Token, FOptionalString& Code, FOptionalString& ExternalToken, FOptionalChallengeSolution& ChallengeSolution, FOptionalString& ProviderNamespace, FOptionalString& RedirectUri, FOptionalString& ThirdParty, FOptionalContextInfo& Context, FOptionalString& RefreshToken, FOptionalString& Username, FOptionalString& ClientId, FOptionalString& Password, FOptionalArrayOfString& Scope, FOptionalMapOfString& InitProperties);
};