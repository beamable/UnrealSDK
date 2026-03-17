#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/AuthV2RevokeRefreshTokensRequestBody.h"

#include "AuthV2RevokeRefreshTokensRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAuthV2RevokeRefreshTokensRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Json", DisplayName="AuthV2RevokeRefreshTokensRequestBody To JSON String")
	static FString AuthV2RevokeRefreshTokensRequestBodyToJsonString(const UAuthV2RevokeRefreshTokensRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Make AuthV2RevokeRefreshTokensRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UAuthV2RevokeRefreshTokensRequestBody* Make(TArray<FString> Tokens, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Break AuthV2RevokeRefreshTokensRequestBody", meta=(NativeBreakFunc))
	static void Break(const UAuthV2RevokeRefreshTokensRequestBody* Serializable, TArray<FString>& Tokens);
};