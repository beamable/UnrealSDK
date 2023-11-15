
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt32.h"
#include "BeamableCore/Public/AutoGen/LeaderboardListResponse.h"

#include "BasicLeaderboardsGetListRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UBasicLeaderboardsGetListRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Skip", Category="Beam")
	FOptionalInt32 Skip = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Limit", Category="Beam")
	FOptionalInt32 Limit = {};

	// Body Params
	

	// Beam Base Request Declaration
	UBasicLeaderboardsGetListRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|Leaderboards", DisplayName="Beam - Make BasicLeaderboardsGetList",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Skip,_Limit,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UBasicLeaderboardsGetListRequest* Make(FOptionalInt32 _Skip, FOptionalInt32 _Limit, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicLeaderboardsGetListSuccess, FBeamRequestContext, Context, UBasicLeaderboardsGetListRequest*, Request, ULeaderboardListResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicLeaderboardsGetListError, FBeamRequestContext, Context, UBasicLeaderboardsGetListRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBasicLeaderboardsGetListComplete, FBeamRequestContext, Context, UBasicLeaderboardsGetListRequest*, Request);

using FBasicLeaderboardsGetListFullResponse = FBeamFullResponse<UBasicLeaderboardsGetListRequest*, ULeaderboardListResponse*>;
DECLARE_DELEGATE_OneParam(FOnBasicLeaderboardsGetListFullResponse, FBasicLeaderboardsGetListFullResponse);
