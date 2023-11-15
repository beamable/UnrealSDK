
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamBackend/SemanticTypes/BeamStatsType.h"
#include "BeamableCore/Public/AutoGen/StatsClientSubscriptionsResponse.h"

#include "GetClientSubscriptionsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetClientSubscriptionsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	FBeamStatsType ObjectId = {};
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UGetClientSubscriptionsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|Stats", DisplayName="Beam - Make GetClientSubscriptions",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetClientSubscriptionsRequest* Make(FBeamStatsType _ObjectId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetClientSubscriptionsSuccess, FBeamRequestContext, Context, UGetClientSubscriptionsRequest*, Request, UStatsClientSubscriptionsResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetClientSubscriptionsError, FBeamRequestContext, Context, UGetClientSubscriptionsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetClientSubscriptionsComplete, FBeamRequestContext, Context, UGetClientSubscriptionsRequest*, Request);

using FGetClientSubscriptionsFullResponse = FBeamFullResponse<UGetClientSubscriptionsRequest*, UStatsClientSubscriptionsResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetClientSubscriptionsFullResponse, FGetClientSubscriptionsFullResponse);
