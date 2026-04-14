#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/AuthV2PasswordAuthRequestBody.h"

#include "AuthV2PasswordAuthRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAuthV2PasswordAuthRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Json", DisplayName="AuthV2PasswordAuthRequestBody To JSON String")
	static FString AuthV2PasswordAuthRequestBodyToJsonString(const UAuthV2PasswordAuthRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Make AuthV2PasswordAuthRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Email, Password, Scope, CustomerId, RealmId, Context, Outer", NativeMakeFunc))
	static UAuthV2PasswordAuthRequestBody* Make(FOptionalString Email, FOptionalString Password, FOptionalString Scope, FOptionalBeamCid CustomerId, FOptionalBeamPid RealmId, FOptionalAuthV2ContextInfo Context, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Break AuthV2PasswordAuthRequestBody", meta=(NativeBreakFunc))
	static void Break(const UAuthV2PasswordAuthRequestBody* Serializable, FOptionalString& Email, FOptionalString& Password, FOptionalString& Scope, FOptionalBeamCid& CustomerId, FOptionalBeamPid& RealmId, FOptionalAuthV2ContextInfo& Context);
};