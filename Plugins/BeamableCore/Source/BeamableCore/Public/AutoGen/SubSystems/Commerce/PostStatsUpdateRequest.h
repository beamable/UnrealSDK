
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/StatSubscriptionNotification.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#include "PostStatsUpdateRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostStatsUpdateRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	int64 ObjectId = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UStatSubscriptionNotification* Body = {};

	// Beam Base Request Declaration
	UPostStatsUpdateRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Commerce|Utils|Make/Break", DisplayName="Make PostStatsUpdate",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostStatsUpdateRequest* Make(int64 _ObjectId, TMap<FString, FString> _StatsBefore, TMap<FString, FString> _StatsAfter, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostStatsUpdateSuccess, FBeamRequestContext, Context, UPostStatsUpdateRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostStatsUpdateError, FBeamRequestContext, Context, UPostStatsUpdateRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostStatsUpdateComplete, FBeamRequestContext, Context, UPostStatsUpdateRequest*, Request);

using FPostStatsUpdateFullResponse = FBeamFullResponse<UPostStatsUpdateRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostStatsUpdateFullResponse, FPostStatsUpdateFullResponse);
