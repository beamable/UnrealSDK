#pragma once

#include "CoreMinimal.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/PushCampaignRequestBody.h"

#include "PushCampaignRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREALMICROSERVICECLIENTS_API UPushCampaignRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Json", DisplayName="PushCampaignRequestBody To JSON String")
	static FString PushCampaignRequestBodyToJsonString(const UPushCampaignRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Make PushCampaignRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UPushCampaignRequestBody* Make(FString Title, FString Body, FString DeepLink, FString CampaignId, FString NodeId, FString GamerTag, FString AccountId, FString CidPid, FString CampaignData, TArray<UPushOffer*> Offers, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Break PushCampaignRequestBody", meta=(NativeBreakFunc))
	static void Break(const UPushCampaignRequestBody* Serializable, FString& Title, FString& Body, FString& DeepLink, FString& CampaignId, FString& NodeId, FString& GamerTag, FString& AccountId, FString& CidPid, FString& CampaignData, TArray<UPushOffer*>& Offers);
};