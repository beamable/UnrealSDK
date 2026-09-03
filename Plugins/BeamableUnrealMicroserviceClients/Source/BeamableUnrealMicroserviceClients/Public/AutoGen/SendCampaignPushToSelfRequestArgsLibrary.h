#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SendCampaignPushToSelfRequestArgs.h"

#include "SendCampaignPushToSelfRequestArgsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API USendCampaignPushToSelfRequestArgsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Json", DisplayName="SendCampaignPushToSelfRequestArgs To JSON String")
	static FString SendCampaignPushToSelfRequestArgsToJsonString(const USendCampaignPushToSelfRequestArgs* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Make SendCampaignPushToSelfRequestArgs", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static USendCampaignPushToSelfRequestArgs* Make(UPushCampaignRequestBody* Request, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Break SendCampaignPushToSelfRequestArgs", meta=(NativeBreakFunc))
	static void Break(const USendCampaignPushToSelfRequestArgs* Serializable, UPushCampaignRequestBody*& Request);
};