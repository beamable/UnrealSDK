
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/StatSubscriptionNotification.h"
#include "AutoGen/CommonResponse.h"

#include "PostStatsUpdateRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostStatsUpdateRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	int64 ObjectId;
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UStatSubscriptionNotification* Body;

	// Beam Base Request Declaration
	UPostStatsUpdateRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer"))
	static UPostStatsUpdateRequest* MakePostStatsUpdateRequest(int64 _ObjectId, TMap<FString, FString> _StatsBefore, TMap<FString, FString> _StatsAfter, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostStatsUpdateSuccess, FBeamRequestContext, Context, UPostStatsUpdateRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostStatsUpdateError, FBeamRequestContext, Context, UPostStatsUpdateRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostStatsUpdateComplete, FBeamRequestContext, Context, UPostStatsUpdateRequest*, Request);

using FPostStatsUpdateFullResponse = FBeamFullResponse<UPostStatsUpdateRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostStatsUpdateFullResponse, FPostStatsUpdateFullResponse);
