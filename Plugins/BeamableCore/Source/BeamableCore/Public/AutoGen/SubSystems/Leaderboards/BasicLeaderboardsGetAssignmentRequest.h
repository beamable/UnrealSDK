
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBool.h"
#include "BeamableCore/Public/AutoGen/LeaderboardAssignmentInfo.h"

#include "BasicLeaderboardsGetAssignmentRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UBasicLeaderboardsGetAssignmentRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Board Id", Category="Beam")
	FString BoardId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Join Board", Category="Beam")
	FOptionalBool bJoinBoard = {};

	// Body Params
	

	// Beam Base Request Declaration
	UBasicLeaderboardsGetAssignmentRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Leaderboards|Utils|Make/Break", DisplayName="Make BasicLeaderboardsGetAssignment",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_bJoinBoard,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UBasicLeaderboardsGetAssignmentRequest* Make(FString _BoardId, FOptionalBool _bJoinBoard, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicLeaderboardsGetAssignmentSuccess, FBeamRequestContext, Context, UBasicLeaderboardsGetAssignmentRequest*, Request, ULeaderboardAssignmentInfo*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnBasicLeaderboardsGetAssignmentError, FBeamRequestContext, Context, UBasicLeaderboardsGetAssignmentRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBasicLeaderboardsGetAssignmentComplete, FBeamRequestContext, Context, UBasicLeaderboardsGetAssignmentRequest*, Request);

using FBasicLeaderboardsGetAssignmentFullResponse = FBeamFullResponse<UBasicLeaderboardsGetAssignmentRequest*, ULeaderboardAssignmentInfo*>;
DECLARE_DELEGATE_OneParam(FOnBasicLeaderboardsGetAssignmentFullResponse, FBasicLeaderboardsGetAssignmentFullResponse);
