#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/AuthV2RefreshTokenAuthRequestBody.h"

#include "AuthV2RefreshTokenAuthRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAuthV2RefreshTokenAuthRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Json", DisplayName="AuthV2RefreshTokenAuthRequestBody To JSON String")
	static FString AuthV2RefreshTokenAuthRequestBodyToJsonString(const UAuthV2RefreshTokenAuthRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Make AuthV2RefreshTokenAuthRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="RefreshToken, CustomerId, RealmId, Context, Outer", NativeMakeFunc))
	static UAuthV2RefreshTokenAuthRequestBody* Make(FOptionalString RefreshToken, FOptionalBeamCid CustomerId, FOptionalBeamPid RealmId, FOptionalAuthV2ContextInfo Context, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Break AuthV2RefreshTokenAuthRequestBody", meta=(NativeBreakFunc))
	static void Break(const UAuthV2RefreshTokenAuthRequestBody* Serializable, FOptionalString& RefreshToken, FOptionalBeamCid& CustomerId, FOptionalBeamPid& RealmId, FOptionalAuthV2ContextInfo& Context);
};