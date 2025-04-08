#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/PasswordAuthRequestBody.h"

#include "PasswordAuthRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPasswordAuthRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Json", DisplayName="PasswordAuthRequestBody To JSON String")
	static FString PasswordAuthRequestBodyToJsonString(const UPasswordAuthRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Make PasswordAuthRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Email, Password, Scope, CustomerId, RealmId, Context, Outer", NativeMakeFunc))
	static UPasswordAuthRequestBody* Make(FOptionalString Email, FOptionalString Password, FOptionalString Scope, FOptionalBeamCid CustomerId, FOptionalBeamPid RealmId, FOptionalContextInfo Context, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Break PasswordAuthRequestBody", meta=(NativeBreakFunc))
	static void Break(const UPasswordAuthRequestBody* Serializable, FOptionalString& Email, FOptionalString& Password, FOptionalString& Scope, FOptionalBeamCid& CustomerId, FOptionalBeamPid& RealmId, FOptionalContextInfo& Context);
};