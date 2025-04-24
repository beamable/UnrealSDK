
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#include "DeleteLeaderboardsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteLeaderboardsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	FString ObjectId = {};
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UDeleteLeaderboardsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Leaderboards|Utils|Make/Break", DisplayName="Make DeleteLeaderboards",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UDeleteLeaderboardsRequest* Make(FString _ObjectId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteLeaderboardsSuccess, FBeamRequestContext, Context, UDeleteLeaderboardsRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteLeaderboardsError, FBeamRequestContext, Context, UDeleteLeaderboardsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDeleteLeaderboardsComplete, FBeamRequestContext, Context, UDeleteLeaderboardsRequest*, Request);

using FDeleteLeaderboardsFullResponse = FBeamFullResponse<UDeleteLeaderboardsRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnDeleteLeaderboardsFullResponse, FDeleteLeaderboardsFullResponse);
