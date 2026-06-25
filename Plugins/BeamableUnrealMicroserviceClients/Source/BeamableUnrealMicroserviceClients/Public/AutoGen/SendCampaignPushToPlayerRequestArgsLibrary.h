#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SendCampaignPushToPlayerRequestArgs.h"

#include "SendCampaignPushToPlayerRequestArgsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API USendCampaignPushToPlayerRequestArgsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Json", DisplayName="SendCampaignPushToPlayerRequestArgs To JSON String")
	static FString SendCampaignPushToPlayerRequestArgsToJsonString(const USendCampaignPushToPlayerRequestArgs* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Make SendCampaignPushToPlayerRequestArgs", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static USendCampaignPushToPlayerRequestArgs* Make(int64 PlayerId, UPushCampaignRequestBody* Request, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Break SendCampaignPushToPlayerRequestArgs", meta=(NativeBreakFunc))
	static void Break(const USendCampaignPushToPlayerRequestArgs* Serializable, int64& PlayerId, UPushCampaignRequestBody*& Request);
};