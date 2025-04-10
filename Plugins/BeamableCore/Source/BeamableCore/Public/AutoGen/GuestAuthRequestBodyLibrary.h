#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GuestAuthRequestBody.h"

#include "GuestAuthRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGuestAuthRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Json", DisplayName="GuestAuthRequestBody To JSON String")
	static FString GuestAuthRequestBodyToJsonString(const UGuestAuthRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Make GuestAuthRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Scope, CustomerId, RealmId, Context, InitProperties, Outer", NativeMakeFunc))
	static UGuestAuthRequestBody* Make(FOptionalString Scope, FOptionalBeamCid CustomerId, FOptionalBeamPid RealmId, FOptionalContextInfo Context, FOptionalMapOfString InitProperties, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Break GuestAuthRequestBody", meta=(NativeBreakFunc))
	static void Break(const UGuestAuthRequestBody* Serializable, FOptionalString& Scope, FOptionalBeamCid& CustomerId, FOptionalBeamPid& RealmId, FOptionalContextInfo& Context, FOptionalMapOfString& InitProperties);
};