#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/AuthV2ExternalAuthRequestBody.h"

#include "AuthV2ExternalAuthRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAuthV2ExternalAuthRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Json", DisplayName="AuthV2ExternalAuthRequestBody To JSON String")
	static FString AuthV2ExternalAuthRequestBodyToJsonString(const UAuthV2ExternalAuthRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Make AuthV2ExternalAuthRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="bHasProviderNamespace, Provider, ProviderNamespace, Token, ChallengeSolution, Scope, CustomerId, RealmId, Context, Outer", NativeMakeFunc))
	static UAuthV2ExternalAuthRequestBody* Make(FOptionalBool bHasProviderNamespace, FOptionalString Provider, FOptionalString ProviderNamespace, FOptionalString Token, FOptionalAuthV2ChallengeSolution ChallengeSolution, FOptionalString Scope, FOptionalBeamCid CustomerId, FOptionalBeamPid RealmId, FOptionalAuthV2ContextInfo Context, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Break AuthV2ExternalAuthRequestBody", meta=(NativeBreakFunc))
	static void Break(const UAuthV2ExternalAuthRequestBody* Serializable, FOptionalBool& bHasProviderNamespace, FOptionalString& Provider, FOptionalString& ProviderNamespace, FOptionalString& Token, FOptionalAuthV2ChallengeSolution& ChallengeSolution, FOptionalString& Scope, FOptionalBeamCid& CustomerId, FOptionalBeamPid& RealmId, FOptionalAuthV2ContextInfo& Context);
};