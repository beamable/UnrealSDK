#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/AuthV2AuthCodeRequestBody.h"

#include "AuthV2AuthCodeRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAuthV2AuthCodeRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Json", DisplayName="AuthV2AuthCodeRequestBody To JSON String")
	static FString AuthV2AuthCodeRequestBodyToJsonString(const UAuthV2AuthCodeRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Make AuthV2AuthCodeRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="AccountId, RedirectUri, CustomerId, RealmId, Context, Scopes, Outer", NativeMakeFunc))
	static UAuthV2AuthCodeRequestBody* Make(FOptionalBeamAccountId AccountId, FOptionalString RedirectUri, FOptionalBeamCid CustomerId, FOptionalBeamPid RealmId, FOptionalAuthV2ContextInfo Context, FOptionalArrayOfString Scopes, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Break AuthV2AuthCodeRequestBody", meta=(NativeBreakFunc))
	static void Break(const UAuthV2AuthCodeRequestBody* Serializable, FOptionalBeamAccountId& AccountId, FOptionalString& RedirectUri, FOptionalBeamCid& CustomerId, FOptionalBeamPid& RealmId, FOptionalAuthV2ContextInfo& Context, FOptionalArrayOfString& Scopes);
};