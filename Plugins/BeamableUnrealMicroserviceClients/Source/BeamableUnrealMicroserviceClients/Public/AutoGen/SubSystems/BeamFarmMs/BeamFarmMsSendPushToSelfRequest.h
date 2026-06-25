
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SendPushToSelfRequestArgs.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SendResult.h"

#include "BeamFarmMsSendPushToSelfRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLEUNREALMICROSERVICECLIENTS_API UBeamFarmMsSendPushToSelfRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	USendPushToSelfRequestArgs* Body = {};

	// Beam Base Request Declaration
	UBeamFarmMsSendPushToSelfRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|BeamFarmMs|Utils|Make/Break", DisplayName="Make BeamFarmMsSendPushToSelf",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UBeamFarmMsSendPushToSelfRequest* Make(FString _Title, FString _Body, FString _DeepLink, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBeamFarmMsSendPushToSelfSuccess, FBeamRequestContext, Context, UBeamFarmMsSendPushToSelfRequest*, Request, USendResult*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBeamFarmMsSendPushToSelfError, FBeamRequestContext, Context, UBeamFarmMsSendPushToSelfRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBeamFarmMsSendPushToSelfComplete, FBeamRequestContext, Context, UBeamFarmMsSendPushToSelfRequest*, Request);

using FBeamFarmMsSendPushToSelfFullResponse = FBeamFullResponse<UBeamFarmMsSendPushToSelfRequest*, USendResult*>;
DECLARE_DELEGATE_OneParam(FOnBeamFarmMsSendPushToSelfFullResponse, FBeamFarmMsSendPushToSelfFullResponse);
