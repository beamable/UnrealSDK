#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/AuthV2GuestAuthRequestBody.h"

#include "AuthV2GuestAuthRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAuthV2GuestAuthRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Json", DisplayName="AuthV2GuestAuthRequestBody To JSON String")
	static FString AuthV2GuestAuthRequestBodyToJsonString(const UAuthV2GuestAuthRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Make AuthV2GuestAuthRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Scope, CustomerId, RealmId, Context, InitProperties, Outer", NativeMakeFunc))
	static UAuthV2GuestAuthRequestBody* Make(FOptionalString Scope, FOptionalBeamCid CustomerId, FOptionalBeamPid RealmId, FOptionalAuthV2ContextInfo Context, FOptionalMapOfString InitProperties, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Break AuthV2GuestAuthRequestBody", meta=(NativeBreakFunc))
	static void Break(const UAuthV2GuestAuthRequestBody* Serializable, FOptionalString& Scope, FOptionalBeamCid& CustomerId, FOptionalBeamPid& RealmId, FOptionalAuthV2ContextInfo& Context, FOptionalMapOfString& InitProperties);
};