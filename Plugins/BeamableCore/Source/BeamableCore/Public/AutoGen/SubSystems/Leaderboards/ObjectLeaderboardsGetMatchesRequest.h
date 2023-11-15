
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"



#include "BeamableCore/Public/AutoGen/MatchMakingMatchesPvpResponse.h"

#include "ObjectLeaderboardsGetMatchesRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UObjectLeaderboardsGetMatchesRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	FString ObjectId = {};
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Pool Size", Category="Beam")
	int32 PoolSize = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Windows", Category="Beam")
	int32 Windows = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Window Size", Category="Beam")
	int32 WindowSize = {};

	// Body Params
	

	// Beam Base Request Declaration
	UObjectLeaderboardsGetMatchesRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|Leaderboards", DisplayName="Beam - Make ObjectLeaderboardsGetMatches",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UObjectLeaderboardsGetMatchesRequest* Make(FString _ObjectId, int32 _PoolSize, int32 _Windows, int32 _WindowSize, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectLeaderboardsGetMatchesSuccess, FBeamRequestContext, Context, UObjectLeaderboardsGetMatchesRequest*, Request, UMatchMakingMatchesPvpResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectLeaderboardsGetMatchesError, FBeamRequestContext, Context, UObjectLeaderboardsGetMatchesRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnObjectLeaderboardsGetMatchesComplete, FBeamRequestContext, Context, UObjectLeaderboardsGetMatchesRequest*, Request);

using FObjectLeaderboardsGetMatchesFullResponse = FBeamFullResponse<UObjectLeaderboardsGetMatchesRequest*, UMatchMakingMatchesPvpResponse*>;
DECLARE_DELEGATE_OneParam(FOnObjectLeaderboardsGetMatchesFullResponse, FObjectLeaderboardsGetMatchesFullResponse);
