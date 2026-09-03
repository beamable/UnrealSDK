#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/FcmConfigStatus.h"

#include "FcmConfigStatusLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API UFcmConfigStatusLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Json", DisplayName="FcmConfigStatus To JSON String")
	static FString FcmConfigStatusToJsonString(const UFcmConfigStatus* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Make FcmConfigStatus", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UFcmConfigStatus* Make(bool bConfigured, bool bPrivateKeyLoaded, FString ProjectId, FString ClientEmail, FString TokenUri, FString Message, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Break FcmConfigStatus", meta=(NativeBreakFunc))
	static void Break(const UFcmConfigStatus* Serializable, bool& bConfigured, bool& bPrivateKeyLoaded, FString& ProjectId, FString& ClientEmail, FString& TokenUri, FString& Message);
};