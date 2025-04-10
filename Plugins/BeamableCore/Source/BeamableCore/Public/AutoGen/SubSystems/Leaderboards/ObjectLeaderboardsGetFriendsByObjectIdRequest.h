
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/LeaderBoardViewResponse.h"

#include "ObjectLeaderboardsGetFriendsByObjectIdRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UObjectLeaderboardsGetFriendsByObjectIdRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	FString ObjectId = {};
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UObjectLeaderboardsGetFriendsByObjectIdRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Leaderboards|Utils|Make/Break", DisplayName="Make ObjectLeaderboardsGetFriendsByObjectId",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UObjectLeaderboardsGetFriendsByObjectIdRequest* Make(FString _ObjectId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectLeaderboardsGetFriendsByObjectIdSuccess, FBeamRequestContext, Context, UObjectLeaderboardsGetFriendsByObjectIdRequest*, Request, ULeaderBoardViewResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectLeaderboardsGetFriendsByObjectIdError, FBeamRequestContext, Context, UObjectLeaderboardsGetFriendsByObjectIdRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnObjectLeaderboardsGetFriendsByObjectIdComplete, FBeamRequestContext, Context, UObjectLeaderboardsGetFriendsByObjectIdRequest*, Request);

using FObjectLeaderboardsGetFriendsByObjectIdFullResponse = FBeamFullResponse<UObjectLeaderboardsGetFriendsByObjectIdRequest*, ULeaderBoardViewResponse*>;
DECLARE_DELEGATE_OneParam(FOnObjectLeaderboardsGetFriendsByObjectIdFullResponse, FObjectLeaderboardsGetFriendsByObjectIdFullResponse);
