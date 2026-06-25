
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SendCampaignPushToPlayerRequestArgs.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/AdminSendResult.h"

#include "BeamFarmMsSendCampaignPushToPlayerRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLEUNREALMICROSERVICECLIENTS_API UBeamFarmMsSendCampaignPushToPlayerRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	USendCampaignPushToPlayerRequestArgs* Body = {};

	// Beam Base Request Declaration
	UBeamFarmMsSendCampaignPushToPlayerRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Make BeamFarmMsSendCampaignPushToPlayer",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UBeamFarmMsSendCampaignPushToPlayerRequest* Make(int64 _PlayerId, UPushCampaignRequestBody* _Request, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBeamFarmMsSendCampaignPushToPlayerSuccess, FBeamRequestContext, Context, UBeamFarmMsSendCampaignPushToPlayerRequest*, Request, UAdminSendResult*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBeamFarmMsSendCampaignPushToPlayerError, FBeamRequestContext, Context, UBeamFarmMsSendCampaignPushToPlayerRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBeamFarmMsSendCampaignPushToPlayerComplete, FBeamRequestContext, Context, UBeamFarmMsSendCampaignPushToPlayerRequest*, Request);

using FBeamFarmMsSendCampaignPushToPlayerFullResponse = FBeamFullResponse<UBeamFarmMsSendCampaignPushToPlayerRequest*, UAdminSendResult*>;
DECLARE_DELEGATE_OneParam(FOnBeamFarmMsSendCampaignPushToPlayerFullResponse, FBeamFarmMsSendCampaignPushToPlayerFullResponse);
