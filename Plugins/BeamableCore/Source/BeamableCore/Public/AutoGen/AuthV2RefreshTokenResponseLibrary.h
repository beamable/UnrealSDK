#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/AuthV2RefreshTokenResponse.h"

#include "AuthV2RefreshTokenResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAuthV2RefreshTokenResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Json", DisplayName="AuthV2RefreshTokenResponse To JSON String")
	static FString AuthV2RefreshTokenResponseToJsonString(const UAuthV2RefreshTokenResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Make AuthV2RefreshTokenResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Token, Created, Outer", NativeMakeFunc))
	static UAuthV2RefreshTokenResponse* Make(FOptionalString Token, FOptionalDateTime Created, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Break AuthV2RefreshTokenResponse", meta=(NativeBreakFunc))
	static void Break(const UAuthV2RefreshTokenResponse* Serializable, FOptionalString& Token, FOptionalDateTime& Created);
};