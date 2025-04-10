
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/LeaderboardCreateRequestBody.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#include "PostLeaderboardsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostLeaderboardsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	FString ObjectId = {};
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	ULeaderboardCreateRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostLeaderboardsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Leaderboards|Utils|Make/Break", DisplayName="Make PostLeaderboards",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_bPartitioned,_FreezeTime,_ScoreName,_CohortSettings,_Permissions,_MaxEntries,_Ttl,_Derivatives,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostLeaderboardsRequest* Make(FString _ObjectId, bool _bSharded, FOptionalBool _bPartitioned, FOptionalInt64 _FreezeTime, FOptionalString _ScoreName, FOptionalLeaderboardCohortSettings _CohortSettings, FOptionalBeamClientPermission _Permissions, FOptionalInt32 _MaxEntries, FOptionalInt64 _Ttl, FOptionalArrayOfString _Derivatives, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostLeaderboardsSuccess, FBeamRequestContext, Context, UPostLeaderboardsRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostLeaderboardsError, FBeamRequestContext, Context, UPostLeaderboardsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostLeaderboardsComplete, FBeamRequestContext, Context, UPostLeaderboardsRequest*, Request);

using FPostLeaderboardsFullResponse = FBeamFullResponse<UPostLeaderboardsRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostLeaderboardsFullResponse, FPostLeaderboardsFullResponse);
