
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableUnrealMicroserviceClients/Public/AutoGen/GetSampleStatRequestArgs.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/LiveOpsDemoMSGetSampleStatResponse.h"

#include "LiveOpsDemoMSGetSampleStatRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLEUNREALMICROSERVICECLIENTS_API ULiveOpsDemoMSGetSampleStatRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UGetSampleStatRequestArgs* Body = {};

	// Beam Base Request Declaration
	ULiveOpsDemoMSGetSampleStatRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|LiveOpsDemoMS|Utils|Make/Break", DisplayName="Make LiveOpsDemoMSGetSampleStat",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static ULiveOpsDemoMSGetSampleStatRequest* Make(int64 _GamerTag, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnLiveOpsDemoMSGetSampleStatSuccess, FBeamRequestContext, Context, ULiveOpsDemoMSGetSampleStatRequest*, Request, ULiveOpsDemoMSGetSampleStatResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnLiveOpsDemoMSGetSampleStatError, FBeamRequestContext, Context, ULiveOpsDemoMSGetSampleStatRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnLiveOpsDemoMSGetSampleStatComplete, FBeamRequestContext, Context, ULiveOpsDemoMSGetSampleStatRequest*, Request);

using FLiveOpsDemoMSGetSampleStatFullResponse = FBeamFullResponse<ULiveOpsDemoMSGetSampleStatRequest*, ULiveOpsDemoMSGetSampleStatResponse*>;
DECLARE_DELEGATE_OneParam(FOnLiveOpsDemoMSGetSampleStatFullResponse, FLiveOpsDemoMSGetSampleStatFullResponse);
