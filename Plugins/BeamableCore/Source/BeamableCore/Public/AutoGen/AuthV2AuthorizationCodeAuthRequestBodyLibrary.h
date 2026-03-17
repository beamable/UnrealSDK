#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/AuthV2AuthorizationCodeAuthRequestBody.h"

#include "AuthV2AuthorizationCodeAuthRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAuthV2AuthorizationCodeAuthRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Json", DisplayName="AuthV2AuthorizationCodeAuthRequestBody To JSON String")
	static FString AuthV2AuthorizationCodeAuthRequestBodyToJsonString(const UAuthV2AuthorizationCodeAuthRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Make AuthV2AuthorizationCodeAuthRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="ClientId, Code, RedirectUri, Scope, CustomerId, RealmId, Context, Outer", NativeMakeFunc))
	static UAuthV2AuthorizationCodeAuthRequestBody* Make(FOptionalString ClientId, FOptionalString Code, FOptionalString RedirectUri, FOptionalString Scope, FOptionalBeamCid CustomerId, FOptionalBeamPid RealmId, FOptionalAuthV2ContextInfo Context, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Break AuthV2AuthorizationCodeAuthRequestBody", meta=(NativeBreakFunc))
	static void Break(const UAuthV2AuthorizationCodeAuthRequestBody* Serializable, FOptionalString& ClientId, FOptionalString& Code, FOptionalString& RedirectUri, FOptionalString& Scope, FOptionalBeamCid& CustomerId, FOptionalBeamPid& RealmId, FOptionalAuthV2ContextInfo& Context);
};