
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SendPushToPlayerRequestArgs.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/AdminSendResult.h"

#include "BeamFarmMsSendPushToPlayerRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLEUNREALMICROSERVICECLIENTS_API UBeamFarmMsSendPushToPlayerRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	USendPushToPlayerRequestArgs* Body = {};

	// Beam Base Request Declaration
	UBeamFarmMsSendPushToPlayerRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Make BeamFarmMsSendPushToPlayer",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UBeamFarmMsSendPushToPlayerRequest* Make(int64 _PlayerId, FString _Title, FString _Body, FString _DeepLink, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBeamFarmMsSendPushToPlayerSuccess, FBeamRequestContext, Context, UBeamFarmMsSendPushToPlayerRequest*, Request, UAdminSendResult*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBeamFarmMsSendPushToPlayerError, FBeamRequestContext, Context, UBeamFarmMsSendPushToPlayerRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBeamFarmMsSendPushToPlayerComplete, FBeamRequestContext, Context, UBeamFarmMsSendPushToPlayerRequest*, Request);

using FBeamFarmMsSendPushToPlayerFullResponse = FBeamFullResponse<UBeamFarmMsSendPushToPlayerRequest*, UAdminSendResult*>;
DECLARE_DELEGATE_OneParam(FOnBeamFarmMsSendPushToPlayerFullResponse, FBeamFarmMsSendPushToPlayerFullResponse);
