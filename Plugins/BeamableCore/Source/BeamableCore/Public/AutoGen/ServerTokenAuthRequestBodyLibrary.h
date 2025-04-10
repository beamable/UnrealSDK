#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ServerTokenAuthRequestBody.h"

#include "ServerTokenAuthRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UServerTokenAuthRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Json", DisplayName="ServerTokenAuthRequestBody To JSON String")
	static FString ServerTokenAuthRequestBodyToJsonString(const UServerTokenAuthRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Make ServerTokenAuthRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="ClientId, ClientSecret, CustomerId, RealmId, Outer", NativeMakeFunc))
	static UServerTokenAuthRequestBody* Make(FOptionalString ClientId, FOptionalString ClientSecret, FOptionalBeamCid CustomerId, FOptionalBeamPid RealmId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Make/Break", DisplayName="Break ServerTokenAuthRequestBody", meta=(NativeBreakFunc))
	static void Break(const UServerTokenAuthRequestBody* Serializable, FOptionalString& ClientId, FOptionalString& ClientSecret, FOptionalBeamCid& CustomerId, FOptionalBeamPid& RealmId);
};