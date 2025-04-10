#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/RefreshTokenAuthRequestBody.h"

#include "RefreshTokenAuthRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API URefreshTokenAuthRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Json", DisplayName="RefreshTokenAuthRequestBody To JSON String")
	static FString RefreshTokenAuthRequestBodyToJsonString(const URefreshTokenAuthRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Make RefreshTokenAuthRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="RefreshToken, CustomerId, RealmId, Context, Outer", NativeMakeFunc))
	static URefreshTokenAuthRequestBody* Make(FOptionalString RefreshToken, FOptionalBeamCid CustomerId, FOptionalBeamPid RealmId, FOptionalContextInfo Context, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Break RefreshTokenAuthRequestBody", meta=(NativeBreakFunc))
	static void Break(const URefreshTokenAuthRequestBody* Serializable, FOptionalString& RefreshToken, FOptionalBeamCid& CustomerId, FOptionalBeamPid& RealmId, FOptionalContextInfo& Context);
};