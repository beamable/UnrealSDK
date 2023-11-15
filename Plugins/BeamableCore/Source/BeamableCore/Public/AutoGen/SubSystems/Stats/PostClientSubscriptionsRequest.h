
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamBackend/SemanticTypes/BeamStatsType.h"
#include "BeamableCore/Public/AutoGen/StatClientSubscriptionRequestBody.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#include "PostClientSubscriptionsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostClientSubscriptionsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	FBeamStatsType ObjectId = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UStatClientSubscriptionRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostClientSubscriptionsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|Stats", DisplayName="Beam - Make PostClientSubscriptions",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostClientSubscriptionsRequest* Make(FBeamStatsType _ObjectId, FBeamGamerTag _TargetGamerTag, TArray<FString> _Keys, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostClientSubscriptionsSuccess, FBeamRequestContext, Context, UPostClientSubscriptionsRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostClientSubscriptionsError, FBeamRequestContext, Context, UPostClientSubscriptionsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostClientSubscriptionsComplete, FBeamRequestContext, Context, UPostClientSubscriptionsRequest*, Request);

using FPostClientSubscriptionsFullResponse = FBeamFullResponse<UPostClientSubscriptionsRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostClientSubscriptionsFullResponse, FPostClientSubscriptionsFullResponse);
