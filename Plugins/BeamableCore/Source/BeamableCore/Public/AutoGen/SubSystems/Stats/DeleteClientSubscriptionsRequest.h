
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamBackend/SemanticTypes/BeamStatsType.h"
#include "BeamableCore/Public/AutoGen/StatClientSubscriptionDeleteRequestBody.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#include "DeleteClientSubscriptionsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteClientSubscriptionsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	FBeamStatsType ObjectId = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UStatClientSubscriptionDeleteRequestBody* Body = {};

	// Beam Base Request Declaration
	UDeleteClientSubscriptionsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|Stats", DisplayName="Beam - Make DeleteClientSubscriptions",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_bDeleteAll,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UDeleteClientSubscriptionsRequest* Make(FBeamStatsType _ObjectId, FBeamGamerTag _TargetGamerTag, TArray<FString> _Keys, FOptionalBool _bDeleteAll, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteClientSubscriptionsSuccess, FBeamRequestContext, Context, UDeleteClientSubscriptionsRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteClientSubscriptionsError, FBeamRequestContext, Context, UDeleteClientSubscriptionsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDeleteClientSubscriptionsComplete, FBeamRequestContext, Context, UDeleteClientSubscriptionsRequest*, Request);

using FDeleteClientSubscriptionsFullResponse = FBeamFullResponse<UDeleteClientSubscriptionsRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnDeleteClientSubscriptionsFullResponse, FDeleteClientSubscriptionsFullResponse);
