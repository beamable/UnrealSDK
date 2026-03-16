#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/AuthV2ServerTokenAuthRequestBody.h"

#include "AuthV2ServerTokenAuthRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAuthV2ServerTokenAuthRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Json", DisplayName="AuthV2ServerTokenAuthRequestBody To JSON String")
	static FString AuthV2ServerTokenAuthRequestBodyToJsonString(const UAuthV2ServerTokenAuthRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Make AuthV2ServerTokenAuthRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="ClientId, ClientSecret, CustomerId, RealmId, Outer", NativeMakeFunc))
	static UAuthV2ServerTokenAuthRequestBody* Make(FOptionalString ClientId, FOptionalString ClientSecret, FOptionalBeamCid CustomerId, FOptionalBeamPid RealmId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Break AuthV2ServerTokenAuthRequestBody", meta=(NativeBreakFunc))
	static void Break(const UAuthV2ServerTokenAuthRequestBody* Serializable, FOptionalString& ClientId, FOptionalString& ClientSecret, FOptionalBeamCid& CustomerId, FOptionalBeamPid& RealmId);
};