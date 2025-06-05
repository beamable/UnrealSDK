
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/IncrementStatRequestArgs.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/LiveOpsDemoMSIncrementStatResponse.h"

#include "LiveOpsDemoMSIncrementStatRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLEUNREALMICROSERVICECLIENTS_API ULiveOpsDemoMSIncrementStatRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UIncrementStatRequestArgs* Body = {};

	// Beam Base Request Declaration
	ULiveOpsDemoMSIncrementStatRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|LiveOpsDemoMS|Utils|Make/Break", DisplayName="Make LiveOpsDemoMSIncrementStat",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static ULiveOpsDemoMSIncrementStatRequest* Make(int64 _GamerTag, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnLiveOpsDemoMSIncrementStatSuccess, FBeamRequestContext, Context, ULiveOpsDemoMSIncrementStatRequest*, Request, ULiveOpsDemoMSIncrementStatResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnLiveOpsDemoMSIncrementStatError, FBeamRequestContext, Context, ULiveOpsDemoMSIncrementStatRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnLiveOpsDemoMSIncrementStatComplete, FBeamRequestContext, Context, ULiveOpsDemoMSIncrementStatRequest*, Request);

using FLiveOpsDemoMSIncrementStatFullResponse = FBeamFullResponse<ULiveOpsDemoMSIncrementStatRequest*, ULiveOpsDemoMSIncrementStatResponse*>;
DECLARE_DELEGATE_OneParam(FOnLiveOpsDemoMSIncrementStatFullResponse, FLiveOpsDemoMSIncrementStatFullResponse);
