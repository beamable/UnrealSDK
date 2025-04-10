
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/StatsUnsubscribeRequestBody.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#include "DeleteSubscribeRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteSubscribeRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UStatsUnsubscribeRequestBody* Body = {};

	// Beam Base Request Declaration
	UDeleteSubscribeRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Stats|Utils|Make/Break", DisplayName="Make DeleteSubscribe",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Subscriptions,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UDeleteSubscribeRequest* Make(FString _Service, FOptionalArrayOfString _Subscriptions, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteSubscribeSuccess, FBeamRequestContext, Context, UDeleteSubscribeRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteSubscribeError, FBeamRequestContext, Context, UDeleteSubscribeRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDeleteSubscribeComplete, FBeamRequestContext, Context, UDeleteSubscribeRequest*, Request);

using FDeleteSubscribeFullResponse = FBeamFullResponse<UDeleteSubscribeRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnDeleteSubscribeFullResponse, FDeleteSubscribeFullResponse);
