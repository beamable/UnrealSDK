
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/IncrementStatRequestArgs.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/LiveOpsDemoMsIncrementStatResponse.h"

#include "LiveOpsDemoMsIncrementStatRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLEUNREALMICROSERVICECLIENTS_API ULiveOpsDemoMsIncrementStatRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UIncrementStatRequestArgs* Body = {};

	// Beam Base Request Declaration
	ULiveOpsDemoMsIncrementStatRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|LiveOpsDemoMs", DisplayName="Beam - Make LiveOpsDemoMsIncrementStat",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static ULiveOpsDemoMsIncrementStatRequest* Make(int64 _UserID, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnLiveOpsDemoMsIncrementStatSuccess, FBeamRequestContext, Context, ULiveOpsDemoMsIncrementStatRequest*, Request, ULiveOpsDemoMsIncrementStatResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnLiveOpsDemoMsIncrementStatError, FBeamRequestContext, Context, ULiveOpsDemoMsIncrementStatRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnLiveOpsDemoMsIncrementStatComplete, FBeamRequestContext, Context, ULiveOpsDemoMsIncrementStatRequest*, Request);

using FLiveOpsDemoMsIncrementStatFullResponse = FBeamFullResponse<ULiveOpsDemoMsIncrementStatRequest*, ULiveOpsDemoMsIncrementStatResponse*>;
DECLARE_DELEGATE_OneParam(FOnLiveOpsDemoMsIncrementStatFullResponse, FLiveOpsDemoMsIncrementStatFullResponse);
