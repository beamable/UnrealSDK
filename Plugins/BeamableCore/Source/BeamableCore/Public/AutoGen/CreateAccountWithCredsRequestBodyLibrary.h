#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/CreateAccountWithCredsRequestBody.h"

#include "CreateAccountWithCredsRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCreateAccountWithCredsRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Json", DisplayName="CreateAccountWithCredsRequestBody To JSON String")
	static FString CreateAccountWithCredsRequestBodyToJsonString(const UCreateAccountWithCredsRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Make CreateAccountWithCredsRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Username, ProviderNamespace, ChallengeSolution, ExternalToken, ProviderService, Password, InitProperties, Outer", NativeMakeFunc))
	static UCreateAccountWithCredsRequestBody* Make(FOptionalString Username, FOptionalString ProviderNamespace, FOptionalChallengeSolution ChallengeSolution, FOptionalString ExternalToken, FOptionalString ProviderService, FOptionalString Password, FOptionalMapOfString InitProperties, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Break CreateAccountWithCredsRequestBody", meta=(NativeBreakFunc))
	static void Break(const UCreateAccountWithCredsRequestBody* Serializable, FOptionalString& Username, FOptionalString& ProviderNamespace, FOptionalChallengeSolution& ChallengeSolution, FOptionalString& ExternalToken, FOptionalString& ProviderService, FOptionalString& Password, FOptionalMapOfString& InitProperties);
};