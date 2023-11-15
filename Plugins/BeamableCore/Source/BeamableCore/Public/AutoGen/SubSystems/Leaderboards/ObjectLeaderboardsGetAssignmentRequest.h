
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"


#include "BeamableCore/Public/AutoGen/LeaderboardAssignmentInfo.h"

#include "ObjectLeaderboardsGetAssignmentRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UObjectLeaderboardsGetAssignmentRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Object Id", Category="Beam")
	FString ObjectId = {};
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UObjectLeaderboardsGetAssignmentRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Backend|Leaderboards", DisplayName="Beam - Make ObjectLeaderboardsGetAssignment",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UObjectLeaderboardsGetAssignmentRequest* Make(FString _ObjectId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectLeaderboardsGetAssignmentSuccess, FBeamRequestContext, Context, UObjectLeaderboardsGetAssignmentRequest*, Request, ULeaderboardAssignmentInfo*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObjectLeaderboardsGetAssignmentError, FBeamRequestContext, Context, UObjectLeaderboardsGetAssignmentRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnObjectLeaderboardsGetAssignmentComplete, FBeamRequestContext, Context, UObjectLeaderboardsGetAssignmentRequest*, Request);

using FObjectLeaderboardsGetAssignmentFullResponse = FBeamFullResponse<UObjectLeaderboardsGetAssignmentRequest*, ULeaderboardAssignmentInfo*>;
DECLARE_DELEGATE_OneParam(FOnObjectLeaderboardsGetAssignmentFullResponse, FObjectLeaderboardsGetAssignmentFullResponse);
