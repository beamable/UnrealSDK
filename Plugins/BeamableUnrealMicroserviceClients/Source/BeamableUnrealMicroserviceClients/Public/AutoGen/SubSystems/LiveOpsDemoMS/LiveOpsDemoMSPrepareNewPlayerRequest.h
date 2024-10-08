
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/PrepareNewPlayerRequestArgs.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/LiveOpsDemoMSPrepareNewPlayerResponse.h"

#include "LiveOpsDemoMSPrepareNewPlayerRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLEUNREALMICROSERVICECLIENTS_API ULiveOpsDemoMSPrepareNewPlayerRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UPrepareNewPlayerRequestArgs* Body = {};

	// Beam Base Request Declaration
	ULiveOpsDemoMSPrepareNewPlayerRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|LiveOpsDemoMS", DisplayName="Beam - Make LiveOpsDemoMSPrepareNewPlayer",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static ULiveOpsDemoMSPrepareNewPlayerRequest* Make(int64 _UserID, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnLiveOpsDemoMSPrepareNewPlayerSuccess, FBeamRequestContext, Context, ULiveOpsDemoMSPrepareNewPlayerRequest*, Request, ULiveOpsDemoMSPrepareNewPlayerResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnLiveOpsDemoMSPrepareNewPlayerError, FBeamRequestContext, Context, ULiveOpsDemoMSPrepareNewPlayerRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnLiveOpsDemoMSPrepareNewPlayerComplete, FBeamRequestContext, Context, ULiveOpsDemoMSPrepareNewPlayerRequest*, Request);

using FLiveOpsDemoMSPrepareNewPlayerFullResponse = FBeamFullResponse<ULiveOpsDemoMSPrepareNewPlayerRequest*, ULiveOpsDemoMSPrepareNewPlayerResponse*>;
DECLARE_DELEGATE_OneParam(FOnLiveOpsDemoMSPrepareNewPlayerFullResponse, FLiveOpsDemoMSPrepareNewPlayerFullResponse);
