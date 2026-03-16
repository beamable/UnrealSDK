#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/AuthV2ListTokensResponse.h"

#include "AuthV2ListTokensResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAuthV2ListTokensResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Json", DisplayName="AuthV2ListTokensResponse To JSON String")
	static FString AuthV2ListTokensResponseToJsonString(const UAuthV2ListTokensResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Make AuthV2ListTokensResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Tokens, Outer", NativeMakeFunc))
	static UAuthV2ListTokensResponse* Make(FOptionalArrayOfAuthV2RefreshTokenResponse Tokens, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Break AuthV2ListTokensResponse", meta=(NativeBreakFunc))
	static void Break(const UAuthV2ListTokensResponse* Serializable, FOptionalArrayOfAuthV2RefreshTokenResponse& Tokens);
};