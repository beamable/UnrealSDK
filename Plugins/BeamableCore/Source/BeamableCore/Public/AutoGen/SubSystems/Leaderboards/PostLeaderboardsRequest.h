
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"


#include "AutoGen/LeaderboardCreateRequestBody.h"
#include "AutoGen/CommonResponse.h"

#include "PostLeaderboardsRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostLeaderboardsRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id")
	FString ObjectId;
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	ULeaderboardCreateRequestBody* Body;

	// Beam Base Request Declaration
	UPostLeaderboardsRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_FreezeTime,_Derivatives,_ScoreName,_CohortSettings,_Permissions,_MaxEntries,_bPartitioned,_Ttl,Outer"))
	static UPostLeaderboardsRequest* MakePostLeaderboardsRequest(FString _ObjectId, FOptionalInt64 _FreezeTime, FOptionalArrayOfString _Derivatives, FOptionalString _ScoreName, FOptionalLeaderboardCohortSettings _CohortSettings, FOptionalClientPermission _Permissions, FOptionalInt32 _MaxEntries, FOptionalBool _bPartitioned, bool _bSharded, FOptionalInt64 _Ttl, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostLeaderboardsSuccess, FBeamRequestContext, Context, UPostLeaderboardsRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostLeaderboardsError, FBeamRequestContext, Context, UPostLeaderboardsRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostLeaderboardsComplete, FBeamRequestContext, Context, UPostLeaderboardsRequest*, Request);

using FPostLeaderboardsFullResponse = FBeamFullResponse<UPostLeaderboardsRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostLeaderboardsFullResponse, FPostLeaderboardsFullResponse);
