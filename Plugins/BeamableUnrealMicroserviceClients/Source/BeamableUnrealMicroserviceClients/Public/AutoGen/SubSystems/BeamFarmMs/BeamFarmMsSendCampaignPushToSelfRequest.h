
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SendCampaignPushToSelfRequestArgs.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SendResult.h"

#include "BeamFarmMsSendCampaignPushToSelfRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLEUNREALMICROSERVICECLIENTS_API UBeamFarmMsSendCampaignPushToSelfRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	USendCampaignPushToSelfRequestArgs* Body = {};

	// Beam Base Request Declaration
	UBeamFarmMsSendCampaignPushToSelfRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Make BeamFarmMsSendCampaignPushToSelf",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UBeamFarmMsSendCampaignPushToSelfRequest* Make(UPushCampaignRequestBody* _Request, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBeamFarmMsSendCampaignPushToSelfSuccess, FBeamRequestContext, Context, UBeamFarmMsSendCampaignPushToSelfRequest*, Request, USendResult*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBeamFarmMsSendCampaignPushToSelfError, FBeamRequestContext, Context, UBeamFarmMsSendCampaignPushToSelfRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBeamFarmMsSendCampaignPushToSelfComplete, FBeamRequestContext, Context, UBeamFarmMsSendCampaignPushToSelfRequest*, Request);

using FBeamFarmMsSendCampaignPushToSelfFullResponse = FBeamFullResponse<UBeamFarmMsSendCampaignPushToSelfRequest*, USendResult*>;
DECLARE_DELEGATE_OneParam(FOnBeamFarmMsSendCampaignPushToSelfFullResponse, FBeamFarmMsSendCampaignPushToSelfFullResponse);
