
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/PrepareNewPlayerRequestArgs.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/LiveOpsDemoMsPrepareNewPlayerResponse.h"

#include "LiveOpsDemoMsPrepareNewPlayerRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLEUNREALMICROSERVICECLIENTS_API ULiveOpsDemoMsPrepareNewPlayerRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UPrepareNewPlayerRequestArgs* Body = {};

	// Beam Base Request Declaration
	ULiveOpsDemoMsPrepareNewPlayerRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|LiveOpsDemoMs", DisplayName="Beam - Make LiveOpsDemoMsPrepareNewPlayer",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static ULiveOpsDemoMsPrepareNewPlayerRequest* Make(int64 _UserID, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnLiveOpsDemoMsPrepareNewPlayerSuccess, FBeamRequestContext, Context, ULiveOpsDemoMsPrepareNewPlayerRequest*, Request, ULiveOpsDemoMsPrepareNewPlayerResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnLiveOpsDemoMsPrepareNewPlayerError, FBeamRequestContext, Context, ULiveOpsDemoMsPrepareNewPlayerRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnLiveOpsDemoMsPrepareNewPlayerComplete, FBeamRequestContext, Context, ULiveOpsDemoMsPrepareNewPlayerRequest*, Request);

using FLiveOpsDemoMsPrepareNewPlayerFullResponse = FBeamFullResponse<ULiveOpsDemoMsPrepareNewPlayerRequest*, ULiveOpsDemoMsPrepareNewPlayerResponse*>;
DECLARE_DELEGATE_OneParam(FOnLiveOpsDemoMsPrepareNewPlayerFullResponse, FLiveOpsDemoMsPrepareNewPlayerFullResponse);
