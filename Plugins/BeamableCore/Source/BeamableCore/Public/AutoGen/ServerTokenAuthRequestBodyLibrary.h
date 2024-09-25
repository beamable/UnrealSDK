#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BeamableCore/Public/AutoGen/ServerTokenAuthRequestBody.h"

#include "ServerTokenAuthRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UServerTokenAuthRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - ServerTokenAuthRequestBody To JSON String")
	static FString ServerTokenAuthRequestBodyToJsonString(const UServerTokenAuthRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make ServerTokenAuthRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="ClientId, ClientSecret, CustomerId, RealmId, Outer", NativeMakeFunc))
	static UServerTokenAuthRequestBody* Make(FOptionalString ClientId, FOptionalString ClientSecret, FOptionalBeamCid CustomerId, FOptionalBeamPid RealmId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break ServerTokenAuthRequestBody", meta=(NativeBreakFunc))
	static void Break(const UServerTokenAuthRequestBody* Serializable, FOptionalString& ClientId, FOptionalString& ClientSecret, FOptionalBeamCid& CustomerId, FOptionalBeamPid& RealmId);
};